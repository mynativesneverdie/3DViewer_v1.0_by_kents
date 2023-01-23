#ifndef OGLW_H
#define OGLW_H

#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets>
#include <cmath>

extern "C" {
#include "../parser/parser.h"
}

class OGLW : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  OGLW(QWidget *parent = nullptr);
  ~OGLW();
  int line_type = 1;
  int perspective = 0;
  float line_width = 1;
  float point_size = 2;
  int point_type = 0;
  float scale = 2;
  QVector3D lineColorV = {1, 1, 1};
  QVector3D pointColorV = {1, 1, 1};
  QColor backgroundColor;
  QColor line_color;
  QColor point_color;

  QString file_str;

  struct info dataset = {0, 0, 0, 0, 0, 0, 0, 0};

  int x_angel = 0;
  int y_angel = 0;
  int z_angel = 0;

  int x_offset = 0;
  int y_offset = 0;
  int z_offset = 0;

protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

private:
  QPoint mouse_position;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

  void setup_conf_file();
  void to_default();
  void read_conf_file();

signals:
  void mouseMove();
};

#endif // OGLW_H
