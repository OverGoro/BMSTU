/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QLabel *move_y_label;
    QLineEdit *move_z_lineEdit;
    QLineEdit *move_y_lineEdit;
    QLineEdit *move_x_lineEdit;
    QLabel *move_x_label;
    QLabel *move_z_label;
    QPushButton *move_pushButton;
    QLabel *move_label;
    QFrame *frame_4;
    QGridLayout *gridLayout_4;
    QLabel *rotate_y_label;
    QLineEdit *rotate_x_lineEdit;
    QLabel *rotate_z_label;
    QLineEdit *rotate_z_lineEdit;
    QLabel *rotate_x_label;
    QLineEdit *rotate_y_lineEdit;
    QPushButton *rotate_pushButton;
    QLabel *rotate_label;
    QFrame *frame_5;
    QGridLayout *gridLayout_6;
    QPushButton *read_file_pushButton;
    QLabel *read_label;
    QLineEdit *read_file_lineEdit;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *center_label;
    QLabel *center_x_label;
    QLineEdit *center_x_lineEdit;
    QLabel *center_y_label;
    QLineEdit *center_y_lineEdit;
    QLabel *center_z_label;
    QLineEdit *center_z_lineEdit;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QLabel *scale_label;
    QLabel *scale_x_label;
    QLineEdit *scale_x_lineEdit;
    QLabel *scale_y_label;
    QLineEdit *scale_y_lineEdit;
    QLabel *scale_z_label;
    QLineEdit *scale_z_lineEdit;
    QPushButton *scale_pushButton;
    QSpacerItem *verticalSpacer;
    GLWidget *openGLWidget;
    QLabel *rc_label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(843, 804);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setMinimumSize(QSize(190, 0));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        move_y_label = new QLabel(frame_2);
        move_y_label->setObjectName(QString::fromUtf8("move_y_label"));
        move_y_label->setMaximumSize(QSize(20, 16777215));

        gridLayout->addWidget(move_y_label, 3, 0, 1, 1);

        move_z_lineEdit = new QLineEdit(frame_2);
        move_z_lineEdit->setObjectName(QString::fromUtf8("move_z_lineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(move_z_lineEdit->sizePolicy().hasHeightForWidth());
        move_z_lineEdit->setSizePolicy(sizePolicy2);
        move_z_lineEdit->setMaximumSize(QSize(150, 16777215));
        move_z_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        move_z_lineEdit->setClearButtonEnabled(false);

        gridLayout->addWidget(move_z_lineEdit, 4, 1, 1, 1);

        move_y_lineEdit = new QLineEdit(frame_2);
        move_y_lineEdit->setObjectName(QString::fromUtf8("move_y_lineEdit"));
        move_y_lineEdit->setMaximumSize(QSize(150, 16777215));
        move_y_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        move_y_lineEdit->setClearButtonEnabled(false);

        gridLayout->addWidget(move_y_lineEdit, 3, 1, 1, 1);

        move_x_lineEdit = new QLineEdit(frame_2);
        move_x_lineEdit->setObjectName(QString::fromUtf8("move_x_lineEdit"));
        move_x_lineEdit->setMaximumSize(QSize(150, 16777215));
        move_x_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        move_x_lineEdit->setClearButtonEnabled(false);

        gridLayout->addWidget(move_x_lineEdit, 2, 1, 1, 1);

        move_x_label = new QLabel(frame_2);
        move_x_label->setObjectName(QString::fromUtf8("move_x_label"));
        move_x_label->setMaximumSize(QSize(20, 16777215));

        gridLayout->addWidget(move_x_label, 2, 0, 1, 1);

        move_z_label = new QLabel(frame_2);
        move_z_label->setObjectName(QString::fromUtf8("move_z_label"));
        move_z_label->setMaximumSize(QSize(20, 16777215));

        gridLayout->addWidget(move_z_label, 4, 0, 1, 1);

        move_pushButton = new QPushButton(frame_2);
        move_pushButton->setObjectName(QString::fromUtf8("move_pushButton"));

        gridLayout->addWidget(move_pushButton, 5, 0, 1, 2);

        move_label = new QLabel(frame_2);
        move_label->setObjectName(QString::fromUtf8("move_label"));
        move_label->setMaximumSize(QSize(200, 16777215));
        move_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(move_label, 1, 0, 1, 2);


        gridLayout_5->addWidget(frame_2, 1, 0, 1, 1);

        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        sizePolicy1.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy1);
        frame_4->setMinimumSize(QSize(190, 0));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        rotate_y_label = new QLabel(frame_4);
        rotate_y_label->setObjectName(QString::fromUtf8("rotate_y_label"));
        rotate_y_label->setMaximumSize(QSize(20, 16777215));

        gridLayout_4->addWidget(rotate_y_label, 3, 0, 1, 1);

        rotate_x_lineEdit = new QLineEdit(frame_4);
        rotate_x_lineEdit->setObjectName(QString::fromUtf8("rotate_x_lineEdit"));
        rotate_x_lineEdit->setMaximumSize(QSize(150, 16777215));
        rotate_x_lineEdit->setFrame(true);
        rotate_x_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        rotate_x_lineEdit->setClearButtonEnabled(false);

        gridLayout_4->addWidget(rotate_x_lineEdit, 2, 1, 1, 1);

        rotate_z_label = new QLabel(frame_4);
        rotate_z_label->setObjectName(QString::fromUtf8("rotate_z_label"));
        rotate_z_label->setMaximumSize(QSize(20, 16777215));

        gridLayout_4->addWidget(rotate_z_label, 4, 0, 1, 1);

        rotate_z_lineEdit = new QLineEdit(frame_4);
        rotate_z_lineEdit->setObjectName(QString::fromUtf8("rotate_z_lineEdit"));
        rotate_z_lineEdit->setMaximumSize(QSize(150, 16777215));
        rotate_z_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        rotate_z_lineEdit->setClearButtonEnabled(false);

        gridLayout_4->addWidget(rotate_z_lineEdit, 4, 1, 1, 1);

        rotate_x_label = new QLabel(frame_4);
        rotate_x_label->setObjectName(QString::fromUtf8("rotate_x_label"));
        rotate_x_label->setMaximumSize(QSize(20, 16777215));

        gridLayout_4->addWidget(rotate_x_label, 2, 0, 1, 1);

        rotate_y_lineEdit = new QLineEdit(frame_4);
        rotate_y_lineEdit->setObjectName(QString::fromUtf8("rotate_y_lineEdit"));
        rotate_y_lineEdit->setMaximumSize(QSize(150, 16777215));
        rotate_y_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        rotate_y_lineEdit->setClearButtonEnabled(false);

        gridLayout_4->addWidget(rotate_y_lineEdit, 3, 1, 1, 1);

        rotate_pushButton = new QPushButton(frame_4);
        rotate_pushButton->setObjectName(QString::fromUtf8("rotate_pushButton"));

        gridLayout_4->addWidget(rotate_pushButton, 5, 0, 1, 2);

        rotate_label = new QLabel(frame_4);
        rotate_label->setObjectName(QString::fromUtf8("rotate_label"));
        rotate_label->setMaximumSize(QSize(16777215, 16777215));
        rotate_label->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(rotate_label, 1, 0, 1, 2);


        gridLayout_5->addWidget(frame_4, 3, 0, 1, 1);

        frame_5 = new QFrame(centralwidget);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setMaximumSize(QSize(190, 16777215));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame_5);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        read_file_pushButton = new QPushButton(frame_5);
        read_file_pushButton->setObjectName(QString::fromUtf8("read_file_pushButton"));

        gridLayout_6->addWidget(read_file_pushButton, 2, 0, 1, 1);

        read_label = new QLabel(frame_5);
        read_label->setObjectName(QString::fromUtf8("read_label"));

        gridLayout_6->addWidget(read_label, 0, 0, 1, 1);

        read_file_lineEdit = new QLineEdit(frame_5);
        read_file_lineEdit->setObjectName(QString::fromUtf8("read_file_lineEdit"));
        read_file_lineEdit->setMaximumSize(QSize(200, 16777215));

        gridLayout_6->addWidget(read_file_lineEdit, 1, 0, 1, 1);


        gridLayout_5->addWidget(frame_5, 4, 0, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(190, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        center_label = new QLabel(frame);
        center_label->setObjectName(QString::fromUtf8("center_label"));
        center_label->setMaximumSize(QSize(200, 16777215));
        center_label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(center_label, 0, 0, 1, 2);

        center_x_label = new QLabel(frame);
        center_x_label->setObjectName(QString::fromUtf8("center_x_label"));
        center_x_label->setMaximumSize(QSize(20, 16777215));

        gridLayout_2->addWidget(center_x_label, 1, 0, 1, 1);

        center_x_lineEdit = new QLineEdit(frame);
        center_x_lineEdit->setObjectName(QString::fromUtf8("center_x_lineEdit"));
        center_x_lineEdit->setMaximumSize(QSize(150, 16777215));
        center_x_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        center_x_lineEdit->setClearButtonEnabled(false);

        gridLayout_2->addWidget(center_x_lineEdit, 1, 1, 1, 1);

        center_y_label = new QLabel(frame);
        center_y_label->setObjectName(QString::fromUtf8("center_y_label"));
        center_y_label->setMaximumSize(QSize(20, 16777215));

        gridLayout_2->addWidget(center_y_label, 2, 0, 1, 1);

        center_y_lineEdit = new QLineEdit(frame);
        center_y_lineEdit->setObjectName(QString::fromUtf8("center_y_lineEdit"));
        center_y_lineEdit->setMaximumSize(QSize(150, 16777215));
        center_y_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        center_y_lineEdit->setClearButtonEnabled(false);

        gridLayout_2->addWidget(center_y_lineEdit, 2, 1, 1, 1);

        center_z_label = new QLabel(frame);
        center_z_label->setObjectName(QString::fromUtf8("center_z_label"));
        center_z_label->setMaximumSize(QSize(20, 16777215));

        gridLayout_2->addWidget(center_z_label, 3, 0, 1, 1);

        center_z_lineEdit = new QLineEdit(frame);
        center_z_lineEdit->setObjectName(QString::fromUtf8("center_z_lineEdit"));
        sizePolicy2.setHeightForWidth(center_z_lineEdit->sizePolicy().hasHeightForWidth());
        center_z_lineEdit->setSizePolicy(sizePolicy2);
        center_z_lineEdit->setMaximumSize(QSize(150, 16777215));
        center_z_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        center_z_lineEdit->setClearButtonEnabled(false);

        gridLayout_2->addWidget(center_z_lineEdit, 3, 1, 1, 1);


        gridLayout_5->addWidget(frame, 0, 0, 1, 1);

        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy1);
        frame_3->setMinimumSize(QSize(190, 0));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        scale_label = new QLabel(frame_3);
        scale_label->setObjectName(QString::fromUtf8("scale_label"));
        scale_label->setMaximumSize(QSize(200, 16777215));
        scale_label->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(scale_label, 0, 0, 1, 2);

        scale_x_label = new QLabel(frame_3);
        scale_x_label->setObjectName(QString::fromUtf8("scale_x_label"));
        scale_x_label->setMaximumSize(QSize(20, 16777215));

        gridLayout_3->addWidget(scale_x_label, 1, 0, 1, 1);

        scale_x_lineEdit = new QLineEdit(frame_3);
        scale_x_lineEdit->setObjectName(QString::fromUtf8("scale_x_lineEdit"));
        scale_x_lineEdit->setMaximumSize(QSize(150, 16777215));
        scale_x_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        scale_x_lineEdit->setClearButtonEnabled(false);

        gridLayout_3->addWidget(scale_x_lineEdit, 1, 1, 1, 1);

        scale_y_label = new QLabel(frame_3);
        scale_y_label->setObjectName(QString::fromUtf8("scale_y_label"));
        scale_y_label->setMaximumSize(QSize(20, 16777215));

        gridLayout_3->addWidget(scale_y_label, 2, 0, 1, 1);

        scale_y_lineEdit = new QLineEdit(frame_3);
        scale_y_lineEdit->setObjectName(QString::fromUtf8("scale_y_lineEdit"));
        scale_y_lineEdit->setMaximumSize(QSize(150, 16777215));
        scale_y_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        scale_y_lineEdit->setClearButtonEnabled(false);

        gridLayout_3->addWidget(scale_y_lineEdit, 2, 1, 1, 1);

        scale_z_label = new QLabel(frame_3);
        scale_z_label->setObjectName(QString::fromUtf8("scale_z_label"));
        scale_z_label->setMaximumSize(QSize(20, 16777215));

        gridLayout_3->addWidget(scale_z_label, 3, 0, 1, 1);

        scale_z_lineEdit = new QLineEdit(frame_3);
        scale_z_lineEdit->setObjectName(QString::fromUtf8("scale_z_lineEdit"));
        scale_z_lineEdit->setMaximumSize(QSize(150, 16777215));
        scale_z_lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        scale_z_lineEdit->setClearButtonEnabled(false);

        gridLayout_3->addWidget(scale_z_lineEdit, 3, 1, 1, 1);

        scale_pushButton = new QPushButton(frame_3);
        scale_pushButton->setObjectName(QString::fromUtf8("scale_pushButton"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scale_pushButton->sizePolicy().hasHeightForWidth());
        scale_pushButton->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(scale_pushButton, 4, 0, 1, 2);


        gridLayout_5->addWidget(frame_3, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 5, 0, 1, 1);

        openGLWidget = new GLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setMinimumSize(QSize(600, 0));

        gridLayout_5->addWidget(openGLWidget, 0, 1, 6, 1);

        rc_label = new QLabel(centralwidget);
        rc_label->setObjectName(QString::fromUtf8("rc_label"));
        rc_label->setFrameShape(QFrame::Box);
        rc_label->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(rc_label, 6, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 843, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        move_y_label->setText(QCoreApplication::translate("MainWindow", "dy:", nullptr));
        move_z_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        move_y_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        move_x_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        move_x_label->setText(QCoreApplication::translate("MainWindow", "dx:", nullptr));
        move_z_label->setText(QCoreApplication::translate("MainWindow", "dz:", nullptr));
        move_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214", nullptr));
        move_label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        rotate_y_label->setText(QCoreApplication::translate("MainWindow", "ay:", nullptr));
        rotate_x_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        rotate_z_label->setText(QCoreApplication::translate("MainWindow", "az:", nullptr));
        rotate_z_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        rotate_x_label->setText(QCoreApplication::translate("MainWindow", "ax:", nullptr));
        rotate_y_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        rotate_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        rotate_label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\260\321\211\320\265\320\275\320\270\320\265", nullptr));
        read_file_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        read_label->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\207\320\270\321\202\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        center_label->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200", nullptr));
        center_x_label->setText(QCoreApplication::translate("MainWindow", "dx:", nullptr));
        center_x_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        center_y_label->setText(QCoreApplication::translate("MainWindow", "dy:", nullptr));
        center_y_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        center_z_label->setText(QCoreApplication::translate("MainWindow", "dz:", nullptr));
        center_z_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        scale_label->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        scale_x_label->setText(QCoreApplication::translate("MainWindow", "kx:", nullptr));
        scale_x_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        scale_y_label->setText(QCoreApplication::translate("MainWindow", "ky:", nullptr));
        scale_y_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        scale_z_label->setText(QCoreApplication::translate("MainWindow", "kz:", nullptr));
        scale_z_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        scale_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        rc_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
