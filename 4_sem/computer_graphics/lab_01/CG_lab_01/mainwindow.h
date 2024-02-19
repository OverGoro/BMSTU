#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "textwidget.h"
#include "painterwidget.h"
#include "triangle.h"

#include <QStandardItemModel>
#include <QMainWindow>
#include <QPointF>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    bool addingMode;                    // Режим добавления точки
    QVector<QPointF> points;            // Точки
public:
    textWidget taskWidget;              // Виджет с заданием
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void clearResult();
public slots:
    /**
     * @brief updateTable Обновление данных в таблице с точками
     */
    void updateTable();

    /**
     * @brief updateTable Загрузка данных из таблицы с точками
     */
    void loadDataFromTable();

    /**
     * @brief addPoint Добавление новой точки
     */
    void addPoint();


private slots:
    void handle_error(int rc);
    void on_add_pushButton_pressed();
    void on_calculate_pushButton_pressed();
    void on_clear_pushButton_pressed();

    void on_aboutProgramAction_triggered();

    void on_save_scale_checkBox_toggled(bool checked);

    void on_exit_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
