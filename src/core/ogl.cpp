#include "ogl.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <locale.h>

float positions[24] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5,
                       0.0, 0.0, 0.5, 0.5, 0.5, 0.0, 0.0, 0.5,
                       0.0, 0.5, 0.5, 0.5, 0.0, 0.5, 0.5, 0.5};

unsigned int indeces[30] = {1, 7, 5, 1, 3, 7, 1, 4, 3, 1, 2, 4, 3, 8, 7,
                            3, 4, 8, 5, 7, 8, 5, 8, 6, 1, 5, 6, 1, 6, 2};

OGLW::OGLW(QWidget *parent) : QOpenGLWidget(parent) { this->read_conf_file(); }

OGLW::~OGLW() {
  free_dataset(&dataset);
  this->setup_conf_file();
}

void OGLW::setup_conf_file() {
  setlocale(LC_ALL, "POSIX");
  char *path_str = (char *)"./config.cfg";

  FILE *file = fopen(path_str, "w");
  if (file != NULL) {
    fprintf(file, "%d %d %f %f %d %f %f %f %f %f %f", line_type, perspective,
            line_width, point_size, point_type, line_color.redF(),
            line_color.greenF(), line_color.blueF(), point_color.redF(),
            point_color.greenF(), point_color.blueF());
    fclose(file);
  }
}

unsigned int OGLW::compile_shader(unsigned int type,
                                  const std::string &source) {
  unsigned int id = glCreateShader(type);

  const char *src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char *message = (char *)alloca(length * sizeof(char));

    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile"
              << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
              << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);

    return 0;
  }

  return id;
}

int OGLW::create_shader(const std::string &vertex_shader,
                        const std::string &fragment_shader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
  unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
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
  setlocale(LC_ALL, "POSIX");
  char *path_str = (char *)"./config.cfg";

  FILE *file = fopen(path_str, "r");
  if (file != NULL) {
    GLfloat line_color_v[3] = {0};
    GLfloat point_color_v[3] = {0};

    int ch_num =
        fscanf(file, "%d %d %f %f %d %f %f %f %f %f %f", &line_type,
               &perspective, &line_width, &point_size, &point_type,
               &(line_color_v[0]), &(line_color_v[1]), &(line_color_v[2]),
               &(point_color_v[0]), &(point_color_v[1]), &(point_color_v[2]));
               
    if (ch_num != 11 || line_type > 1 || line_type < 0 || perspective > 1 ||
        perspective < 0 || line_width > 5 || line_width < 1 ||
        point_size > 10 || point_size < 1 || point_type > 2 || point_type < 0 ||
        line_color_v[0] < 0 || line_color_v[0] > 1 || line_color_v[1] < 0 ||
        line_color_v[1] > 1 || line_color_v[2] > 1 || line_color_v[2] < 0 ||
        point_color_v[0] > 1 || point_color_v[0] < 0 || point_color_v[1] > 1 ||
        point_color_v[1] < 0 || point_color_v[2] > 1 || point_color_v[2] < 0) {
      this->to_default();
    } else {
      line_color.setRgbF(line_color_v[0], line_color_v[1], line_color_v[2]);
      point_color.setRgbF(point_color_v[0], point_color_v[1], point_color_v[2]);
    }

    std::fclose(file);
  } else {
    this->to_default();
  }
}

void OGLW::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  mat_rotate.setToIdentity();

  background_color.setRgb(0, 0, 0);
}

void OGLW::paintGL() {
  move_axis(&dataset, x_shift - x_move, y_shift - y_move, z_shift - z_move);
  x_shift = x_move;
  y_shift = y_move;
  z_shift = z_move;

  mat_perspective.setToIdentity();
  if (perspective) {
    mat_perspective.perspective(ANGEL, HEIGHT / WIDTH, NEAR, FAR);
    mat_perspective.translate(0, 0, DEPTH);
  }

  mat_norm.setToIdentity();
  mat_norm *= 1 / dataset.max_v * scale;
  mat_norm.setColumn(3, {0, 0, 0, 1});

  mat_projection = mat_norm * mat_rotate * mat_perspective;

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, dataset.index_v * sizeof(float), dataset.arr_v,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

  unsigned int ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataset.index_f * sizeof(unsigned int),
               dataset.arr_f, GL_DYNAMIC_DRAW);

  std::string vertex_shader =
      "#version 330 core\n"
      "layout (location = 0) in vec3 position;\n"
      "uniform mat4 projection;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = projection * vec4(position, 1.0);\n"
      "}\n\0";
  std::string fragment_shader =
      "#version 330 core\n"
      "uniform vec3 color;\n"
      "void main()\n"
      "{\n"
      "   gl_FragColor = vec4(color.x, color.y, color.z, 1);\n"
      "}\n\0";

  unsigned int shader = create_shader(vertex_shader, fragment_shader);
  glUseProgram(shader);

  GLint projection_id = glGetUniformLocation(shader, "projection");
  glUniformMatrix4fv(projection_id, 1, GL_TRUE, mat_projection.data());

  GLint color_id = glGetUniformLocation(shader, "color");
  const GLfloat point_color_v[3] = {point_color.redF(), point_color.greenF(),
                                    point_color.blueF()};
  glUniform3fv(color_id, 1, point_color_v);

  // Set background
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPointSize(point_size);
  glLineWidth(line_width);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Draw dots
  if (point_type == 2) {
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, dataset.index_v);
    glDisable(GL_POINT_SMOOTH);
  }
  if (point_type == 1) {
    glDrawArrays(GL_POINTS, 0, dataset.index_v);
  }
  if (point_type == 0) {
    glDrawArrays(GL_POINT_SMOOTH, 0, dataset.index_v);
  }

  const GLfloat line_color_v[3] = {line_color.redF(), line_color.greenF(),
                                   line_color.blueF()};
  glUniform3fv(color_id, 1, line_color_v);

  if (line_type) {
    glLineStipple(3, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glDrawElements(GL_LINES, dataset.index_f, GL_UNSIGNED_INT, nullptr);
}

QMatrix4x4 OGLW::rotate(int x, int y, int z) {
  double cosx = cos(x * M_PI / 180);
  double cosy = cos(y * M_PI / 180);
  double cosz = cos(z * M_PI / 180);
  double sinx = sin(x * M_PI / 180);
  double siny = sin(y * M_PI / 180);
  double sinz = sin(z * M_PI / 180);

  return QMatrix4x4(cosy * cosz, sinx * siny * cosz - cosx * sinz,
                    cosx * siny * cosz + sinx * sinz, 0, cosy * sinz,
                    sinx * siny * sinz + cosx * cosz,
                    cosx * siny * sinz - sinx * cosz, 0, -siny, sinx * cosy,
                    cosx * cosy, 0, 0, 0, 0, 1);
}

void OGLW::resizeGL(int w, int h) {}

void OGLW::mousePressEvent(QMouseEvent *mouse) {
  mouse_position = mouse->pos();
}

void OGLW::mouseMoveEvent(QMouseEvent *mouse) {
  x_offset = mouse->pos().y() - mouse_position.y();
  y_offset = mouse->pos().x() - mouse_position.x();

  mat_rotate = rotate(x_offset, y_offset, z_offset);

  update();
}
