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
  int lineType = 1;    // 1 for stipple
  int perspective = 0; // 1 for on perspective mode
  float lineWidth = 1; // 1 is default and min, max 5
  float pointSize = 2; // 1 is default, max 10, min 2
  int pointType = 2;   // 0 - disable, 1 - circle, 2 - square
  QVector3D lineColorV = {1, 1, 1};
  QVector3D pointColorV = {1, 1, 1};
  QColor backgroundColor;
  QColor lineColor;
  QColor pointColor;

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
