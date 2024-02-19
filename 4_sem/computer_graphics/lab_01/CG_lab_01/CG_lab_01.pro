QT       += core gui
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    geometricoperations.cpp \
    main.cpp \
    mainwindow.cpp \
    paintertext.cpp \
    painterwidget.cpp \
    pointstableview.cpp \
    tableitemdelegate.cpp \
    test_geometricoperations.cpp \
    textwidget.cpp \
    triangle.cpp

HEADERS += \
    error.h \
    geometricoperations.h \
    mainwindow.h \
    paintertext.h \
    painterwidget.h \
    pointstableview.h \
    tableitemdelegate.h \
    test_geometricoperations.h \
    textwidget.h \
    triangle.h

FORMS += \
    mainwindow.ui \
    textwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
