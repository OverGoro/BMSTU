#include "plotterwidget.h"

PlotterWidget::PlotterWidget(QWidget *parrent)
    :QChartView(parrent)
{
}

PlotterWidget::PlotterWidget(const PlotterWidget &pw)
{
}

void PlotterWidget::setLines(const std::vector<std::vector<QPointF>> &lines,
                             QString title, std::vector<QString> lines_titles)
{
    chart.removeAllSeries();
    size_t title_i = 0;
    for (auto & l : lines)
    {
        QLineSeries *series = new QLineSeries();
        for (auto & p : l)
            series->append(p);
        if (title_i < lines_titles.size())
            series->setName(lines_titles[title_i]);
        title_i++;
        chart.addSeries(series);
    }

    chart.setTitle(title);

    chart.legend()->setVisible(true);
    chart.legend()->setAlignment(Qt::AlignRight);


    chart.createDefaultAxes();

    chart.setAnimationOptions(QChart::SeriesAnimations);

    this->setChart(&chart);
    this->setRenderHint(QPainter::Antialiasing);
}

void PlotterWidget::setSplines(const std::vector<std::vector<QPointF>> &lines,
                               QString title, std::vector<QString> lines_titles)
{
    chart.removeAllSeries();
    size_t title_i = 0;
    for (auto & l : lines)
    {
        QSplineSeries *series = new QSplineSeries();
        for (auto & p : l)
            series->append(p);
        if (title_i < lines_titles.size())
            series->setName(lines_titles[title_i]);
        title_i++;
        chart.addSeries(series);
    }

    chart.legend()->setVisible(true);
    chart.legend()->setAlignment(Qt::AlignRight);


    chart.createDefaultAxes();

    chart.setAnimationOptions(QChart::SeriesAnimations);

    this->setChart(&chart);
    this->setRenderHint(QPainter::Antialiasing);
}

void PlotterWidget::setBars(const std::vector<double> &data, QString title, std::vector<QString> bar_titles)
{
    chart.removeAllSeries();
    QBarSeries *series = new QBarSeries();
    for (size_t i = 0; i < data.size(); i++)
    {
        if (bar_titles.size() > i)
        {
            QBarSet *bs = new QBarSet(bar_titles[i]);
            *bs << data[i];
            series->append(bs);
        }
    }

    chart.addSeries(series);

    chart.legend()->setVisible(true);
    chart.legend()->setAlignment(Qt::AlignRight);


    chart.createDefaultAxes();

    chart.setAnimationOptions(QChart::SeriesAnimations);

    this->setChart(&chart);
    this->setRenderHint(QPainter::Antialiasing);
}
