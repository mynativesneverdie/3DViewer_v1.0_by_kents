#include "ogl.h"

#include <cstdio>
#include <fstream>

OGLW::OGLW(QWidget *parent) : QOpenGLWidget(parent) { this->read_conf_file(); }

OGLW::~OGLW() {
  this->setup_conf_file();
}

void OGLW::setup_conf_file() {
  char *path_str = (char *)"./config.cfg";

  FILE *file = fopen(path_str, "w");
  if (file != NULL) {
    fprintf(file, "%d %d %f %f %d %f %f %f %f %f %f", lineType, perspective,
            lineWidth, pointSize, pointType, lineColorV[0], lineColorV[1],
            lineColorV[2], pointColorV[0], pointColorV[1], pointColorV[2]);
    fclose(file);
  }
}

void OGLW::to_default() {
  lineType = 0;
  perspective = 0;
  lineWidth = 1;
  pointSize = 2;
  pointType = 0;
  lineColor = {1, 1, 1};
  pointColor = {1, 1, 1};
}

void OGLW::read_conf_file() {
  char *path_str = (char *)"./config.cfg";

  FILE *file = fopen(path_str, "r");
  if (file != NULL) {
    int ch_num = fscanf(file, "%d %d %f %f %d %f %f %f %f %f %f", &lineType,
                        &perspective, &lineWidth, &pointSize, &pointType,
                        &lineColorV[0], &lineColorV[1], &lineColorV[2],
                        &pointColorV[0], &pointColorV[1], &pointColorV[2]);
    if (ch_num != 11 || lineType > 1 || lineType < 0 || perspective > 1 ||
        perspective < 0 || lineWidth > 5 || lineWidth < 1 || pointSize > 10 ||
        pointSize < 1 || pointType > 2 || pointType < 0 || lineColorV.x() > 1 ||
        lineColorV.x() < 0 || lineColorV.y() > 1 || lineColorV.y() < 0 ||
        lineColorV.z() > 1 || lineColorV.z() < 0 || pointColorV.x() > 1 ||
        pointColorV.x() < 0 || pointColorV.y() > 1 || pointColorV.y() < 0 ||
        pointColorV.z() > 1 || pointColorV.z() < 0) {
      this->to_default();
    }

    lineColor.setRgbF(lineColorV.x(), lineColorV.y(), lineColorV.z());
    pointColor.setRgbF(pointColorV.x(), pointColorV.y(), pointColorV.z());
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
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(1, 1, 1);

  x_angel += x_offset;
  y_angel += y_offset;
  z_angel += z_offset;

  rotate(dataset.index_v, dataset.arr_v, dataset.arr_v_copy, x_angel, y_angel, z_angel);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPointSize(5);

  glEnableClientState(GL_VERTEX_ARRAY);

  // Draw dots
  glVertexPointer(3, GL_FLOAT, 0, dataset.arr_v_copy);
  glDrawArrays(GL_POINTS, 0, dataset.index_v / 3);

  // Draw polygons
  int k = 0;

  for (int i = 0; i < dataset.index_p; i++) {
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

  // printf("hhh %f %f %f\n", dataset.arr_v_copy[0], dataset.arr_v_copy[1], dataset.arr_v_copy[2]);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void OGLW::resizeGL(int w, int h) {}

void OGLW::mousePressEvent(QMouseEvent *mouse) {
  mouse_position = mouse->pos();
}

void OGLW::mouseMoveEvent(QMouseEvent *mouse) {
  y_offset = mouse->pos().y() - mouse_position.y();
  x_offset = mouse->pos().x() - mouse_position.x();

  // qDebug("%d %d\n", y_angel, x_angel);

  update();

  emit mouseMove();
}
