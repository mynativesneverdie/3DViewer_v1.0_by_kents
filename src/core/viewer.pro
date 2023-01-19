QT += core gui opengl openglwidgets
QT += 3dcore 3dextras

include(../gif_image_qt/src/gifimage/qtgifimage.pri)
# QT += gifimage

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"
DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ogl.cpp \
    ../parser/parser.c \
    ../parser/rotate.c

HEADERS += \
    mainwindow.h \
    ogl.h
    ../parser/parser.h

FORMS += \
    mainwindow.ui

# LIBS += -lOpenGL

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    style.qrc
