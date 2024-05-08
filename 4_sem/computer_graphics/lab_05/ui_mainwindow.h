/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "painterwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *painter_frame;
    QVBoxLayout *verticalLayout_4;
    PainterWidget *painter_widget;
    QFrame *paramaters_frame;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *x_center_label;
    QLineEdit *x_center_lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *y_center_label;
    QLineEdit *y_center_lineEdit;
    QPushButton *addPoint_pushButton;
    QPushButton *closeFigure_pushButton;
    QTableView *tableView;
    QPushButton *pushButton;
    QPushButton *fill_pushButton;
    QPushButton *fillDelay_pushButton;
    QLabel *label_3;
    QPushButton *background_color_pushButton;
    QPushButton *line_color_pushButton;
    QPushButton *fillColor_pushButton;
    QPushButton *clear_pushButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(724, 565);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(9999999, 1080));
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        painter_frame = new QFrame(centralwidget);
        painter_frame->setObjectName("painter_frame");
        painter_frame->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(painter_frame->sizePolicy().hasHeightForWidth());
        painter_frame->setSizePolicy(sizePolicy1);
        painter_frame->setMinimumSize(QSize(500, 500));
        painter_frame->setMaximumSize(QSize(4000, 4000));
        painter_frame->setFrameShape(QFrame::StyledPanel);
        painter_frame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(painter_frame);
        verticalLayout_4->setObjectName("verticalLayout_4");
        painter_widget = new PainterWidget(painter_frame);
        painter_widget->setObjectName("painter_widget");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(painter_widget->sizePolicy().hasHeightForWidth());
        painter_widget->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(painter_widget);


        gridLayout->addWidget(painter_frame, 1, 1, 2, 1);

        paramaters_frame = new QFrame(centralwidget);
        paramaters_frame->setObjectName("paramaters_frame");
        sizePolicy1.setHeightForWidth(paramaters_frame->sizePolicy().hasHeightForWidth());
        paramaters_frame->setSizePolicy(sizePolicy1);
        paramaters_frame->setMinimumSize(QSize(0, 0));
        paramaters_frame->setMaximumSize(QSize(200, 16777215));
        paramaters_frame->setFrameShape(QFrame::StyledPanel);
        paramaters_frame->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(paramaters_frame);
        verticalLayout_6->setSpacing(4);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        x_center_label = new QLabel(paramaters_frame);
        x_center_label->setObjectName("x_center_label");
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(x_center_label->sizePolicy().hasHeightForWidth());
        x_center_label->setSizePolicy(sizePolicy3);
        x_center_label->setMinimumSize(QSize(0, 20));
        x_center_label->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(x_center_label);

        x_center_lineEdit = new QLineEdit(paramaters_frame);
        x_center_lineEdit->setObjectName("x_center_lineEdit");
        sizePolicy3.setHeightForWidth(x_center_lineEdit->sizePolicy().hasHeightForWidth());
        x_center_lineEdit->setSizePolicy(sizePolicy3);
        x_center_lineEdit->setMinimumSize(QSize(0, 20));
        x_center_lineEdit->setMaximumSize(QSize(16777215, 20));

        horizontalLayout->addWidget(x_center_lineEdit);


        verticalLayout_6->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        y_center_label = new QLabel(paramaters_frame);
        y_center_label->setObjectName("y_center_label");
        sizePolicy3.setHeightForWidth(y_center_label->sizePolicy().hasHeightForWidth());
        y_center_label->setSizePolicy(sizePolicy3);
        y_center_label->setMinimumSize(QSize(0, 20));
        y_center_label->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(y_center_label);

        y_center_lineEdit = new QLineEdit(paramaters_frame);
        y_center_lineEdit->setObjectName("y_center_lineEdit");
        sizePolicy3.setHeightForWidth(y_center_lineEdit->sizePolicy().hasHeightForWidth());
        y_center_lineEdit->setSizePolicy(sizePolicy3);
        y_center_lineEdit->setMinimumSize(QSize(0, 20));
        y_center_lineEdit->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(y_center_lineEdit);


        verticalLayout_6->addLayout(horizontalLayout_2);

        addPoint_pushButton = new QPushButton(paramaters_frame);
        addPoint_pushButton->setObjectName("addPoint_pushButton");
        addPoint_pushButton->setMinimumSize(QSize(0, 20));
        addPoint_pushButton->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(addPoint_pushButton);

        closeFigure_pushButton = new QPushButton(paramaters_frame);
        closeFigure_pushButton->setObjectName("closeFigure_pushButton");
        closeFigure_pushButton->setMinimumSize(QSize(0, 20));
        closeFigure_pushButton->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(closeFigure_pushButton);

        tableView = new QTableView(paramaters_frame);
        tableView->setObjectName("tableView");

        verticalLayout_6->addWidget(tableView);

        pushButton = new QPushButton(paramaters_frame);
        pushButton->setObjectName("pushButton");
        pushButton->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setPointSize(16);
        pushButton->setFont(font);

        verticalLayout_6->addWidget(pushButton);

        fill_pushButton = new QPushButton(paramaters_frame);
        fill_pushButton->setObjectName("fill_pushButton");

        verticalLayout_6->addWidget(fill_pushButton);

        fillDelay_pushButton = new QPushButton(paramaters_frame);
        fillDelay_pushButton->setObjectName("fillDelay_pushButton");

        verticalLayout_6->addWidget(fillDelay_pushButton);

        label_3 = new QLabel(paramaters_frame);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 20));
        label_3->setMaximumSize(QSize(16777215, 20));
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setFrameShadow(QFrame::Plain);

        verticalLayout_6->addWidget(label_3);

        background_color_pushButton = new QPushButton(paramaters_frame);
        background_color_pushButton->setObjectName("background_color_pushButton");
        background_color_pushButton->setMinimumSize(QSize(0, 20));
        background_color_pushButton->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(background_color_pushButton);

        line_color_pushButton = new QPushButton(paramaters_frame);
        line_color_pushButton->setObjectName("line_color_pushButton");
        line_color_pushButton->setMinimumSize(QSize(0, 20));
        line_color_pushButton->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(line_color_pushButton);

        fillColor_pushButton = new QPushButton(paramaters_frame);
        fillColor_pushButton->setObjectName("fillColor_pushButton");

        verticalLayout_6->addWidget(fillColor_pushButton);

        clear_pushButton = new QPushButton(paramaters_frame);
        clear_pushButton->setObjectName("clear_pushButton");
        clear_pushButton->setMinimumSize(QSize(0, 20));
        clear_pushButton->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(clear_pushButton);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        gridLayout->addWidget(paramaters_frame, 1, 0, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 724, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\233\320\240 5", nullptr));
        x_center_label->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        x_center_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        y_center_label->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        y_center_lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        addPoint_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\321\203", nullptr));
        closeFigure_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\274\320\272\320\275\321\203\321\202\321\214 \321\204\320\270\320\263\321\203\321\200\321\203", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\360\237\240\224", nullptr));
        fill_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\320\260\321\201\320\270\321\202\321\214", nullptr));
        fillDelay_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\320\260\321\201\320\270\321\202\321\214 \321\201 \320\267\320\260\320\264\320\265\321\200\320\266\320\272\320\276\320\271", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\245\320\276\320\273\321\201\321\202", nullptr));
        background_color_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\206\320\262\320\265\321\202 \321\204\320\276\320\275\320\260", nullptr));
        line_color_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\206\320\262\320\265\321\202 \320\273\320\270\320\275\320\270\320\271", nullptr));
        fillColor_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\206\320\262\320\265\321\202 \320\267\320\260\320\273\320\270\320\262\320\272\320\270", nullptr));
        clear_pushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
