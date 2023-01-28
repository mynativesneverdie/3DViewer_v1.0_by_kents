#ifndef OGLW_H
#define OGLW_H

#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets>
#include <cmath>

#define WIDTH 360.0f
#define HEIGHT 480.0f
#define NEAR 0.1f
#define FAR 100.0f
#define ANGEL 90.0f
#define DEPTH -2.0f

extern "C" {
#include "../parser/s21_parser.h"
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

  QMatrix4x4 mat_projection;
  QMatrix4x4 mat_norm;
  QMatrix4x4 mat_rotate;
  QMatrix4x4 mat_perspective;

  // QVector3D line_color_v = {1, 1, 1};
  QVector3D point_color_v = {1, 1, 1};
  QColor background_color;
  QColor line_color;
  QColor point_color;

  QString file_str;

  struct info dataset = {0, 0, 0, 0, 0, 0};

  float x_offset = 0;
  float y_offset = 0;
  float z_offset = 0;
  
  float x_shift = 0;
  float y_shift = 0;
  float z_shift = 0;

  float x_move = 0;
  float y_move = 0;
  float z_move = 0;

  QMatrix4x4 rotate(int x, int y, int z);


protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

private:
  QPoint mouse_position;

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

  int create_shader(const std::string &vertex_shader,
                    const std::string &fragment_shader);
  unsigned int compile_shader(unsigned int type, const std::string &source);

  void setup_conf_file();
  void to_default();
  void read_conf_file();


signals:
  void mouseMove();
};

#endif // OGLW_H
