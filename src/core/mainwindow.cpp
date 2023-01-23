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
  connect(ui->pushButton_2, SIGNAL(pressed()), this, SLOT(bmp_screen()));
  connect(ui->pushButton_3, SIGNAL(pressed()), this, SLOT(jpg_screen()));
  connect(ui->radioButton_3, SIGNAL(pressed()), this, SLOT(on_radioButton_3_pressed()));
  connect(ui->radioButton_4, SIGNAL(pressed()), this, SLOT(on_radioButton_4_pressed()));
  connect(ui->radioButton_5, SIGNAL(pressed()), this, SLOT(on_radioButton_5_pressed()));
  connect(ui->radioButton_solid, SIGNAL(pressed()), this, SLOT(on_radioButton_solid_pressed()));
  connect(ui->radioButton_dashed, SIGNAL(pressed()), this, SLOT(on_radioButton_dashed_pressed()));
}

void Main_Window::press_start_gif() {
  ui->pushButton_4->setEnabled(0);

  gif = new QGifImage;
  gif->setDefaultDelay(1000 / gif_fps);
  
  start_time = 0;
  gif_timer = new QTimer(this);

  connect(gif_timer, SIGNAL(timeout()), this, SLOT(create_frame()));
  gif_timer->start(1000 / gif_fps);
}

void Main_Window::create_frame() {
  if (start_time != GIF_TIME) {
    QPixmap gif_screen(OGLWidget->size());

    OGLWidget->render(&gif_screen);
    QImage image;
    image = gif_screen.toImage();

    gif->addFrame(image, 1000 / gif_fps);

    start_time += 1000 / gif_fps;
  } else {
    gif_timer->stop();
    ui->pushButton_4->setEnabled(1);
    
    time_t now = time(0);
    tm *time = localtime(&now);
    QDir d = QFileInfo(PROJECT_PATH).absoluteDir();
    d.setPath(QDir::cleanPath(d.filePath(QStringLiteral(".."))));
    QString path = d.path();
    QString name = path + "/gif/" + QString::number(time->tm_hour) + "-" +
                   QString::number(time->tm_min) + "-" +
                   QString::number(time->tm_sec) + ".gif";
    gif->save(name);
    free(gif);
  }
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
  OGLWidget->point_type = 2;
  OGLWidget->update();
}

void Main_Window::on_radioButton_4_pressed() {
  OGLWidget->point_type = 1;
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

 void Main_Window::on_BackColorSlider_valueChanged(int value) {
   OGLWidget->backgroundColor.setHsl(value, 255, 127);
   OGLWidget->update();
 }

void Main_Window::on_horizontalSlider_9_valueChanged(int value) {
  OGLWidget->line_color.setHsl(value, 255, 127);
  OGLWidget->update();
}

void Main_Window::on_horizontalSlider_12_valueChanged(int value) {
  OGLWidget->point_color.setHsl(value, 255, 127);
  OGLWidget->update();
}

void Main_Window::on_radioButton_solid_pressed()
{
    OGLWidget->line_type = 0;
    OGLWidget->update();
}

void Main_Window::on_radioButton_dashed_pressed()
{
    OGLWidget->line_type = 1;
    OGLWidget->update();
}

