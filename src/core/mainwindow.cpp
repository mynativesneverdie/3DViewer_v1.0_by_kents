#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <chrono>

#include "ogl.h"

Main_Window::Main_Window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Main_Window) {
  ui->setupUi(this);

  OGLWidget = new OGLW;
  ui->gridLayout_2->addWidget(OGLWidget, 0, 0);

  init_sliders();

  connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(choose_file_pressed()));
  connect(ui->pushButton_4, SIGNAL(pressed()), this, SLOT(press_start_gif()));
  connect(ui->pushButton_5, SIGNAL(pressed()), this, SLOT(press_stop_gif()));
  connect(ui->pushButton_2, SIGNAL(pressed()), this, SLOT(bmp_screen()));
  connect(ui->pushButton_3, SIGNAL(pressed()), this, SLOT(jpg_screen()));
}

void Main_Window::create_frame() {
  if (!ui->pushButton_4->isEnabled()) {
    QPixmap screen_gif(OGLWidget->size());
    OGLWidget->render(&screen_gif);

    QImage gif_image = screen_gif.toImage();

    gif->addFrame(gif_image, 1000 / gif_fps);
  }
}

void Main_Window::press_start_gif() {
  ui->pushButton_4->setEnabled(0);
  gif = new QGifImage;

  gif->setDefaultDelay(1000 / gif_fps);

  gif_timer = new QTimer(this);
  connect(gif_timer, SIGNAL(timeout()), this, SLOT(create_frame()));
  gif_timer->start(1000 / gif_fps);
}

void Main_Window::press_stop_gif() {
  ui->pushButton_4->setEnabled(1);
  gif_timer->stop();

  unsigned int now_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  QString name = "./gif/" + QString::number(now_time) + ".gif";

  gif->save(name);
  
  free(gif);
}

void Main_Window::jpg_screen() {
  unsigned int now_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  QString name = "./screens/" + QString::number(now_time) + ".jpeg";

  QPixmap pixmap(OGLWidget->size() * 2);
  pixmap.setDevicePixelRatio(2);
  OGLWidget->render(&pixmap);

  pixmap.save(name, "JPEG", 100);
}

void Main_Window::bmp_screen() {
  unsigned int now_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  QString name = "./screens/" + QString::number(now_time) + ".bmp";

  QPixmap pixmap(OGLWidget->size() * 2);
  pixmap.setDevicePixelRatio(2);
  OGLWidget->render(&pixmap);

  pixmap.save(name, "BMP", 100);
}

void Main_Window::init_sliders() {
  ui->horizontalSlider_13->setValue(OGLWidget->point_size * 10);
  ui->horizontalSlider_10->setValue(OGLWidget->line_width * 10);
  ui->horizontalSlider_11->setValue(OGLWidget->scale * 10);

  if (OGLWidget->point_type == 2) {
    ui->radioButton_5->toggle();
  } else if (OGLWidget->point_type == 1) {
    ui->radioButton_4->toggle();
  } else {
    ui->radioButton_3->toggle();
  }

  // if (OGLWidget->line_type) {
  //   ui->DashedEdgeButton->toggle();
  // } else {
  //   ui->SolidEdgeButton->toggle();
  // }

  // if (OGLWidget->perspective)
  //   ui->PerspectivePrButton->toggle();
  // else
  //   ui->OrthoPrButton->toggle();

  ui->horizontalSlider_9->setValue(OGLWidget->line_color.hslHue());
  ui->horizontalSlider_12->setValue(OGLWidget->point_color.hslHue());
}

void Main_Window::choose_file_pressed() {
  OGLWidget->file_str =
      QFileDialog::getOpenFileName(this, tr("Choose an obj file"),
                                   QDir::homePath(), tr("Text Files (*.obj)"));
  ui->lineEdit->setText(OGLWidget->file_str);
  if (!OGLWidget->file_str.isEmpty()) {
    parse_file((char *)OGLWidget->file_str.toStdString().c_str(),
               &(OGLWidget->dataset));
    OGLWidget->update();

    ui->lineEdit_14->setText(QString::number(OGLWidget->dataset.index_p));
    ui->lineEdit_13->setText(QString::number(OGLWidget->dataset.index_v / 3));
  }
}

Main_Window::~Main_Window() {
  free_dataset(&(OGLWidget->dataset));
  delete OGLWidget;
  delete ui;
}

void Main_Window::on_radioButton_5_pressed() {
  OGLWidget->point_type = 1;
  OGLWidget->update();
}

void Main_Window::on_radioButton_4_pressed() {
  OGLWidget->point_type = 2;
  OGLWidget->update();
}

void Main_Window::on_radioButton_3_pressed() {
  OGLWidget->point_type = 0;
  OGLWidget->update();
}

void Main_Window::on_horizontalSlider_10_valueChanged(int value) {
  OGLWidget->line_width = value / 10.0;
  OGLWidget->update();
}

void Main_Window::on_horizontalSlider_13_valueChanged(int value) {
  OGLWidget->point_size = value / 10.0;
  OGLWidget->update();
}

void Main_Window::on_horizontalSlider_11_valueChanged(int value) {
  OGLWidget->scale = (30 - 0.3) * value / 100;
  OGLWidget->update();
}

// void MainWindow::on_BackColorSlider_valueChanged(int value) {
//   OGLWidget->backgroundColor.setHsl(value, 110,100);
//   OGLWidget->update();
// }

void Main_Window::on_horizontalSlider_9_valueChanged(int value) {
  OGLWidget->line_color.setHsl(value, 255, 127);
  OGLWidget->update();
}

void Main_Window::on_horizontalSlider_12_valueChanged(int value) {
  OGLWidget->point_color.setHsl(value, 255, 127);
  OGLWidget->update();
}
