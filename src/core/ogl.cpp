#include "ogl.h"

#include <cstdio>
#include <fstream>

OGLW::OGLW(QWidget *parent) : QOpenGLWidget(parent) { this->read_conf_file(); }

OGLW::~OGLW() { this->setup_conf_file(); }

void OGLW::setup_conf_file() {
  char *path_str = (char *)"./config.cfg";

  FILE *file = fopen(path_str, "w");
  if (file != NULL) {
    fprintf(file, "%d %d %f %f %d %f %f %f %f %f %f", line_type, perspective,
            line_width, point_size, point_type, lineColorV[0], lineColorV[1],
            lineColorV[2], pointColorV[0], pointColorV[1], pointColorV[2]);
    fclose(file);
  }
}

void OGLW::to_default() {
  line_type = 0;
  perspective = 0;
  line_width = 1;
  point_size = 2;
  point_type = 0;
  line_color = {1, 1, 1};
  point_color = {1, 1, 1};
}

void OGLW::read_conf_file() {
  char *path_str = (char *)"./config.cfg";

  FILE *file = fopen(path_str, "r");
  if (file != NULL) {
    int ch_num = fscanf(file, "%d %d %f %f %d %f %f %f %f %f %f", &line_type,
                        &perspective, &line_width, &point_size, &point_type,
                        &lineColorV[0], &lineColorV[1], &lineColorV[2],
                        &pointColorV[0], &pointColorV[1], &pointColorV[2]);
    if (ch_num != 11 || line_type > 1 || line_type < 0 || perspective > 1 ||
        perspective < 0 || line_width > 5 || line_width < 1 ||
        point_size > 10 || point_size < 1 || point_type > 2 || point_type < 0 ||
        lineColorV.x() > 1 || lineColorV.x() < 0 || lineColorV.y() > 1 ||
        lineColorV.y() < 0 || lineColorV.z() > 1 || lineColorV.z() < 0 ||
        pointColorV.x() > 1 || pointColorV.x() < 0 || pointColorV.y() > 1 ||
        pointColorV.y() < 0 || pointColorV.z() > 1 || pointColorV.z() < 0) {
      this->to_default();
    }

    line_color.setRgbF(lineColorV.x(), lineColorV.y(), lineColorV.z());
    point_color.setRgbF(pointColorV.x(), pointColorV.y(), pointColorV.z());
    std::fclose(file);
  } else {
    this->to_default();
  }
}

void OGLW::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  backgroundColor.setRgb(0, 0, 0);
}

void OGLW::paintGL() {
  // Set background
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set angel
  if (x_offset || y_offset || z_offset) {
    x_angel += x_offset;
    y_angel += y_offset;
    z_angel += z_offset;
  }

  rotate(dataset.index_v, dataset.arr_v, dataset.arr_v_copy, x_angel, y_angel,
         z_angel);

  // Normalization
  float norm = 1.0 / (dataset.max_v) * scale;

  for (unsigned int i = 0; i < dataset.index_v; i++) {
    dataset.arr_v_copy[i] *= norm;
  }

  // Draw block
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPointSize(point_size);
  glLineWidth(line_width);

  glEnableClientState(GL_VERTEX_ARRAY);

  // Set dots color
  glColor3f(point_color.redF(), point_color.greenF(), point_color.blueF());

  // Draw dots
  glVertexPointer(3, GL_FLOAT, 0, dataset.arr_v_copy);
  if (point_type == 2) {
      glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, dataset.index_v / 3);
      glDisable(GL_POINT_SMOOTH);
  }
  if (point_type == 1) {
      glDrawArrays(GL_POINTS, 0, dataset.index_v / 3);
  }
  if (point_type == 0) {
      glDrawArrays(GL_POINT_SMOOTH, 0, dataset.index_v / 3);
  }

  // Set line color and type
  glColor3f(line_color.redF(), line_color.greenF(), line_color.blueF());
  if (line_type) {
      glLineStipple(3, 0x00FF);
      glEnable(GL_LINE_STIPPLE);
  } else {
      glDisable(GL_LINE_STIPPLE);
  }

  // Draw polygons
  int k = 0;

  for (unsigned int i = 0; i < dataset.index_p; i++) {
    int coords_num = dataset.arr_p[i];
    float array[coords_num * 3] = {0};

    for (int j = 0; j < coords_num; j++, k++) {
      int plane = dataset.arr_f[k] - 1;

      array[j * 3 + 0] = dataset.arr_v_copy[plane * 3 + 0];
      array[j * 3 + 1] = dataset.arr_v_copy[plane * 3 + 1];
      array[j * 3 + 2] = dataset.arr_v_copy[plane * 3 + 2];
    }

    glVertexPointer(3, GL_FLOAT, 0, array);
    glDrawArrays(GL_POLYGON, 0, coords_num);
  }

  glDisableClientState(GL_VERTEX_ARRAY);

  x_offset = 0;
  y_offset = 0;
  z_offset = 0;
}

void OGLW::resizeGL(int w, int h) {}

void OGLW::mousePressEvent(QMouseEvent *mouse) {
  mouse_position = mouse->pos();
}

void OGLW::mouseMoveEvent(QMouseEvent *mouse) {
  y_offset = mouse->pos().y() - mouse_position.y();
  x_offset = mouse->pos().x() - mouse_position.x();

  update();
  emit mouseMove();
}
