#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "ogl.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Main_Window; }
QT_END_NAMESPACE

class Main_Window : public QMainWindow
{
    Q_OBJECT

public:
    Main_Window(QWidget *parent = nullptr);
    ~Main_Window();

    OGLW *OGLWidget;

    void press_gif();
    void one_gif();


private:
    Ui::Main_Window *ui;
    QGifImage *gif;

    int start_time, tmp_time;
    float time_print;
    const int gif_fps = 10, gif_length = 5;
    QTimer *timer;
};
#endif // MAIN_WINDOW_H
