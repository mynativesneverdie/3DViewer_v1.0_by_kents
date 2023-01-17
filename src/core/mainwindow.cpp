#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "ogl.h"

Main_Window::Main_Window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Main_Window) {
  ui->setupUi(this);

  OGLWidget = new OGLW;
  ui->gridLayout_2->addWidget(OGLWidget, 0, 0);

  connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(choose_file_pressed()));
}

void Main_Window::press_gif() {
  gif = new QGifImage;
  gif->setDefaultDelay(1000 / gif_fps);

  start_time = 0, tmp_time = 1000 / gif_fps;
  timer = new QTimer(this);

  connect(timer, SIGNAL(timeout()), this, SLOT(oneGif()));
  timer->start(1000 / gif_fps);
}

void Main_Window::one_gif() {
  if (start_time == tmp_time) {
    QPixmap screenGIF(OGLWidget->size()); // *2
    //        screenGIF.setDevicePixelRatio(2);  // improves quality. mult the
    //        size by 2 line above ^
    OGLWidget->render(&screenGIF);
    QImage image;
    image = screenGIF.toImage();
    gif->addFrame(image, 1000 / gif_fps);
    time_print = (float)start_time / 1e3; // GIF time in seconds
    //        with 0.1 second precision (50 updates)
    // ui->Counter->setNum((int)(time_print + 1));
    tmp_time += 1000 / gif_fps;
  }
  if (start_time == 1000 * gif_length) {
    time_t now = time(0);
    tm *time = localtime(&now);
    QDir d = QFileInfo(PROJECT_PATH).absoluteDir();
    d.setPath(QDir::cleanPath(d.filePath(QStringLiteral(".."))));
    QString path = d.path();
    QString name = path + "/gifs/" + QString::number(time->tm_hour) + "-" +
                   QString::number(time->tm_min) + "-" +
                   QString::number(time->tm_sec) + ".gif";
    gif->save(name);
    free(gif);

    timer->stop();
    // ui->Counter->setText("");
  }
  start_time += 1000 / gif_fps;
}

void Main_Window::choose_file_pressed() {
  OGLWidget->file_str =
      QFileDialog::getOpenFileName(this, tr("Choose an obj file"),
                                   QDir::homePath(), tr("Text Files (*.obj)"));
  ui->lineEdit->setText(OGLWidget->file_str);
  if (!OGLWidget->file_str.isEmpty()) {
    parse_file((char *)OGLWidget->file_str.toStdString().c_str(), &(OGLWidget->dataset));
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
