QT += core gui opengl widgets
QT += 3dcore 3dextras

#greaterThan(QT_MAJOR_VERSION, 6): QT += openglwidgets
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../qtgifimage/src/gifimage/qtgifimage.pri)

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"
DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ogl.cpp \
    ../parser/parser.c \
    ../parser/move.c

HEADERS += \
    mainwindow.h \
    ogl.h
    ../parser/parser.h

FORMS += \
    mainwindow.ui

LIBS += -lOpenGL

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    style.qrc
