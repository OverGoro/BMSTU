#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "moveaction.h"
#include "rotateaction.h"
#include "scaleaction.h"

#include <QWidgetAction>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Настрока меню правки
    this->historyWidget = new HistoryWidget(); // Создание виджета с истоией изменений

    QMenu *history_menu = ui->menubar->findChild<QMenu *>("history_menu");          // Получение меню правки
    QMenu *showhistory_menu = history_menu->findChild<QMenu *>("showhistory_menu"); // Получение подменю просмотра истории
    QWidgetAction *historyWidgetAction = new QWidgetAction(history_menu);           // Создание виджета-действия
    historyWidgetAction->setDefaultWidget(historyWidget);                           // Установка виджета с историей изменений
    showhistory_menu->addAction(historyWidgetAction);                               // Добавление виджета с историей изменений в подменю
    connect(historyWidget, &HistoryWidget::changed, this, &MainWindow::redraw);     // Связка с перерисовкой


    // Настройка виджетов параметров инструментов
    this->moveParametersWidget = qobject_cast<moveParameters *>(ui->parameters_stackedWidget->widget(1));
    this->rotateParametersWidget = qobject_cast<RotateParameters *>(ui->parameters_stackedWidget->widget(2));
    this->scaleParametersWidget = qobject_cast<ScaleParameters *>(ui->parameters_stackedWidget->widget(3));

    connect(moveParametersWidget, &moveParameters::applied, this, &MainWindow::move);
    connect(rotateParametersWidget, &RotateParameters::applied, this, &MainWindow::rotate);
    connect(scaleParametersWidget, &ScaleParameters::applied, this, &MainWindow::scale);

    // Настройка расчетной ширины / высоты в отрисовщике
    ui->painter_widget->setCountWidth(6);
    ui->painter_widget->setCountHeight(6);

    // Добавление элментов в отрисовщик
    auto bodytop = [](double x){return sqrt(1 - pow(x, 2) / 3);};
    auto bodybottom = [](double x){return -sqrt(1 - pow(x, 2) / 3);};

    ui->painter_widget->addByFunc(bodytop, -1.5, 1.732, 100);
    ui->painter_widget->addByFunc(bodybottom, -1.5, 1.732, 100);

    ui->painter_widget->addByFunc([](double x){return sqrt(0.25 - (x + 1.5) * (x + 1.5));}, -2, -1, 130);
    ui->painter_widget->addByFunc([](double x){return -sqrt(0.25 - pow(x + 1.5, 2));}, -2, -1, 130);

    ui->painter_widget->addByFunc([](double x){return sqrt(0.25 - (x + 1.5) * (x + 1.5));}, -2, -1, 130);
    ui->painter_widget->addByFunc([](double x){return -sqrt(0.25 - pow(x + 1.5, 2));}, -2, -1, 130);

    ui->painter_widget->addByFunc([](double x){return 0.2 + sqrt(1/64.0 - (x + 1.5) * (x + 1.5));}, -1.625, -1.375, 10);
    ui->painter_widget->addByFunc([](double x){return 0.2 - sqrt(1/64.0 - pow(x + 1.5, 2));}, -1.625, -1.375, 10);


    ui->painter_widget->addLines({{{-1.7,-0.2},{-1.3,-0.2}},
                                  {{-0.7,bodytop(0.72)},{-0.5,1.4}},
                                  {{-0.5,1.4},{0.8, 1.4}},
                                  {{0.8, 1.4},{0.5, bodytop(0.5)}}});
    ui->painter_widget->addLines({{{1.602,0.38},{2,0.7}},
                                  {{2,0.7},{3,0.7}},
                                  {{3,0.7},{2.7, 0.2}},
                                  {{2.7, 0.2},{3, -0.3}},
                                  {{3, -0.3},{1.66, -0.28}}});
    ui->painter_widget->addLines({{{-0.7,bodybottom(0.7)},{-0.4, -1.4}},
                                  {{-0.4,-1.4},{0.5,-1.4}},
                                  {{0.5,-1.4},{0.3, bodybottom(0.3)}}});

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::move(double dx, double dy)
{
    QVector2D realDxy = ui->painter_widget->getCountVector(QVector2D(dx,dy));
    MoveAction *act = new MoveAction(ui->painter_widget, realDxy.x(), realDxy.y());
    this->historyWidget->commandStack.push(act);
    update();
}

void MainWindow::rotate(double cx, double cy, double a)
{
    QPointF realCxy = ui->painter_widget->getCountPoint(QPointF(cx,cy));
    RotateAction *act = new RotateAction(ui->painter_widget, realCxy.x(), realCxy.y(), a);
    this->historyWidget->commandStack.push(act);
    update();
}

void MainWindow::scale(double cx, double cy, double kx, double ky)
{
    QPointF realCxy = ui->painter_widget->getCountPoint(QPointF(cx,cy));
    ScaleAction *act = new ScaleAction(ui->painter_widget, realCxy.x(), realCxy.y(), kx, ky);
    this->historyWidget->commandStack.push(act);
    update();
}

void MainWindow::redraw()
{
    update();
}


void MainWindow::on_moveMode_pushButton_toggled(bool checked)
{
    if (checked)
    {
        ui->scaleMode_pushButton->setChecked(false);
        ui->rotateMode_pushButton->setChecked(false);
        ui->parameters_stackedWidget->setCurrentIndex(1);
    }
}


void MainWindow::on_rotateMode_pushButton_toggled(bool checked)
{
    if (checked)
    {
        ui->scaleMode_pushButton->setChecked(false);
        ui->moveMode_pushButton->setChecked(false);
        ui->parameters_stackedWidget->setCurrentIndex(2);
    }
}


void MainWindow::on_scaleMode_pushButton_toggled(bool checked)
{
    if (checked)
    {
        ui->rotateMode_pushButton->setChecked(false);
        ui->moveMode_pushButton->setChecked(false);
        ui->parameters_stackedWidget->setCurrentIndex(3);
    }
}



void MainWindow::on_backward_action_triggered()
{
    this->historyWidget->undo();
    update();
}


void MainWindow::on_forward_action_triggered()
{
    this->historyWidget->redo();
    update();
}

