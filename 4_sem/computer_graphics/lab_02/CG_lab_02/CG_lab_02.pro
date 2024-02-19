QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    historywidget.cpp \
    main.cpp \
    mainwindow.cpp \
    moveaction.cpp \
    moveparameters.cpp \
    painterwidget.cpp \
    rotateaction.cpp \
    rotateparameters.cpp \
    scaleaction.cpp \
    scaleparameters.cpp

HEADERS += \
    historywidget.h \
    mainwindow.h \
    moveaction.h \
    moveparameters.h \
    painterwidget.h \
    rotateaction.h \
    rotateparameters.h \
    scaleaction.h \
    scaleparameters.h

FORMS += \
    historywidget.ui \
    mainwindow.ui \
    moveparameters.ui \
    rotateparameters.ui \
    scaleparameters.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
