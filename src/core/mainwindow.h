#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "qgifimage.h"
#include <QMainWindow>
#include <Qt3DCore/QEntity>

#include "ogl.h"

#define GIF_TIME 5000

QT_BEGIN_NAMESPACE
namespace Ui {
class Main_Window;
}
QT_END_NAMESPACE

class Main_Window : public QMainWindow {
  Q_OBJECT

public:
  Main_Window(QWidget *parent = nullptr);
  ~Main_Window();

  OGLW *OGLWidget;

private slots:
  void press_start_gif();
  void choose_file_pressed();

  void on_horizontalSlider_13_valueChanged(int value);
  void on_horizontalSlider_10_valueChanged(int value);
  void on_horizontalSlider_9_valueChanged(int value);
  void on_horizontalSlider_12_valueChanged(int value);
  void on_horizontalSlider_11_valueChanged(int value);
  void on_BackColorSlider_valueChanged(int value);

  void on_radioButton_3_pressed();
  void on_radioButton_4_pressed();
  void on_radioButton_5_pressed();
  void on_radioButton_6_pressed();
  void on_radioButton_7_pressed();

  void create_frame();
  void jpg_screen();
  void bmp_screen();

  void on_radioButton_solid_pressed();

  void on_radioButton_dashed_pressed();

private:
  Ui::Main_Window *ui;
  void init_sliders();
  QGifImage *gif;

  

  int start_time;
  const int gif_fps = 10, gif_length = 5;
  QTimer *gif_timer;
};
#endif // MAIN_WINDOW_H
