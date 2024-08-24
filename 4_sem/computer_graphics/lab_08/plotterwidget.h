#ifndef PLOTTERWIDGET_H
#define PLOTTERWIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QSplineSeries>
#include <QBarSet>
#include <QBarSeries>

class PlotterWidget : public QChartView
{
    Q_OBJECT
private:
    QChart chart;
public:
    PlotterWidget(QWidget *parrent = 0);
    PlotterWidget(const PlotterWidget &pw);
//    void paintEvent(QPaintEvent *event);
//    void resizeEvent(QResizeEvent *event);
public slots:
    void setLines(const std::vector<std::vector<QPointF>> &lines,
                  QString title, std::vector<QString> lines_titles);
    void setSplines(const std::vector<std::vector<QPointF>> &lines,
                    QString title, std::vector<QString> lines_titles);
    void setBars(const std::vector<double> &data,
                 QString title, std::vector<QString> bar_titles);

};

#endif // PLOTTERWIDGET_H
