QT       += core gui
QT      += openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas.cpp \
    color.cpp \
    drawer.cpp \
    elements_link.cpp \
    elements_link_array.cpp \
    error.cpp \
    figure.cpp \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    move_coefficients.cpp \
    point.cpp \
    points_array.cpp \
    rotate_coefficients.cpp \
    scale_coefficients.cpp

HEADERS += \
    canvas.h \
    color.h \
    drawer.h \
    elements_link.h \
    elements_link_array.h \
    error.h \
    figure.h \
    glwidget.h \
    mainwindow.h \
    manager.h \
    move_coefficients.h \
    point.h \
    points_array.h \
    rotate_coefficients.h \
    scale_coefficients.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../build-OOP_lab_01-Desktop-Debug/pnts \
    ../build-OOP_lab_01-Desktop-Debug/pntsp
