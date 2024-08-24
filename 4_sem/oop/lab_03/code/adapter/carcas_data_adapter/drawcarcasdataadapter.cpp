#include "drawcarcasdataadapter.h"
#include "ProjectionAdapterSolution.h"
#include "QDebug"

void DrawCarcasDataAdapter::request() {
    // for (int i = 0; i < carcas_data->points.size(); i++)
    // {
    //     std::set<Edge> tmp_edges;
    //     for (const auto &edge : carcas_data->edges)
    //     {
    //         if (edge.getFirstPointID() == i || edge.getSecondPointID() == i)
    //             tmp_edges.insert(edge);
    //     }
    //     for (const auto &e1 : tmp_edges)
    //     {
    //         for (const auto &e2 : tmp_edges)
    //         {
    //             if (e1 != e2)
    //             {
    //                 int i_1 = e1.getFirstPointID() != i ? e1.getFirstPointID() : e1.getSecondPointID();
    //                 int i_2 = e2.getFirstPointID() != i ? e2.getFirstPointID() : e2.getSecondPointID();

    //                 auto pp1 = std::make_shared<Point>();
    //                 auto pp2 = std::make_shared<Point>();
    //                 auto pp3 = std::make_shared<Point>();

    //                 ProjectionPerspectiveCameraAdapter(camera, pp1, carcas_data->points[i]).request();
    //                 ProjectionPerspectiveCameraAdapter(camera, pp2, carcas_data->points[i_1]).request();
    //                 ProjectionPerspectiveCameraAdapter(camera, pp3, carcas_data->points[i_2]).request();

    //                 drawer->setTriangleZBuffer(*pp1, *pp2, *pp3);
    //             }
    //         }
    //     }
    // }
    for (const auto &edge : carcas_data->edges)
    {
        auto pp1 = std::make_shared<Point>();
        auto pp2 = std::make_shared<Point>();

        ProjectionAdapterSolution().create(camera, pp1, carcas_data->points[edge.getFirstPointID()])->request();
        ProjectionAdapterSolution().create(camera, pp2, carcas_data->points[edge.getSecondPointID()])->request();
        // drawer->drawLineWithZBuffer(*pp1, *pp2);
        // qDebug() << pp1->getX() << pp1->getY() << pp2->getX() << pp2->getY();
        if (pp1->getZ() >= 0 && pp2->getZ() >= 0)
            drawer->drawLine(pp1->getX(), pp1->getY(), pp2->getX(), pp2->getY());
    }
}

