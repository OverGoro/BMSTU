#include "QTDrawer.h"
#include "qdebug.h"

void QtDrawer::drawLine(double x_1, double y_1, double x_2, double y_2)
{
    scene->addLine(x_1, y_1, x_2, y_2);
}

void QtDrawer::drawPoint(double x, double y)
{
    scene->addLine(x,y,x,y);
}
void QtDrawer::clearPoint(double x, double y)
{
    auto c = scene->backgroundBrush().color();
    scene->addLine(x,y,x,y, scene->backgroundBrush().color());
}

void QtDrawer::clear()
{
    scene->clear();
    scene->setBackgroundBrush(QBrush(Qt::white));
}

void QtDrawer::initializeZBuffer(int width, int height)
{
    z_buffer.clear();
    z_buffer.resize(height, std::vector<double>(width, std::numeric_limits<double>::infinity()));\
}

void QtDrawer::clearZBuffer()
{
    for (auto &row : z_buffer)
    {
        std::fill(row.begin(), row.end(), std::numeric_limits<double>::infinity());
    }
}

bool QtDrawer::isInBounds(int x, int y)
{
    return (x >= 0 && x < z_buffer[0].size() && y >= 0 && y < z_buffer.size());
}

void QtDrawer::setTriangleZBuffer(const Point &p1, const Point &p2, const Point &p3)
{
    // Функция для вычисления значения на краю
    auto edgeFunction = [](const Point &a, const Point &b, const Point &c) -> double
    {
        return (c.getX() - a.getX()) * (b.getY() - a.getY()) - (c.getY() - a.getY()) * (b.getX() - a.getX());
    };

    int minX = std::min({static_cast<int>(p1.getX()), static_cast<int>(p2.getX()), static_cast<int>(p3.getX())});
    int minY = std::min({static_cast<int>(p1.getY()), static_cast<int>(p2.getY()), static_cast<int>(p3.getY())});
    int maxX = std::max({static_cast<int>(p1.getX()), static_cast<int>(p2.getX()), static_cast<int>(p3.getX())});
    int maxY = std::max({static_cast<int>(p1.getY()), static_cast<int>(p2.getY()), static_cast<int>(p3.getY())});

    int width = z_buffer[0].size();
    int height = z_buffer.size();

    // Ensure coordinates are within bounds
    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, width - 1);
    maxY = std::min(maxY, height - 1);

    double area = edgeFunction(p1, p2, p3);
    if (area == 0)
    {
        return;
    }

    // Упорядочим точки по Y
    const Point* pts[3] = { &p1, &p2, &p3 };
    if (pts[1]->getY() < pts[0]->getY()) std::swap(pts[0], pts[1]);
    if (pts[2]->getY() < pts[0]->getY()) std::swap(pts[0], pts[2]);
    if (pts[2]->getY() < pts[1]->getY()) std::swap(pts[1], pts[2]);

    int start_y = std::max(static_cast<int>(pts[0]->getY()), minY);
    int end_y = std::min(static_cast<int>(pts[2]->getY()), maxY);

    bool secondHalf = false;

    fillLineZbuffer(p1, p2);
    fillLineZbuffer(p2, p3);
    fillLineZbuffer(p3, p1);
    // Основной цикл по строкам (y)
    for (int y = start_y + 1; y <= end_y - 1; ++y)
    {
        if (y > pts[1]->getY() || pts[1]->getY() == pts[0]->getY())
        {
            secondHalf = true;
        }
        int segmentHeight = secondHalf ? pts[2]->getY() - pts[1]->getY() : pts[1]->getY() - pts[0]->getY();

        double alpha = static_cast<double>(y - pts[0]->getY()) / (pts[2]->getY() - pts[0]->getY());
        double beta = static_cast<double>(y - (secondHalf ? pts[1]->getY() : pts[0]->getY())) / segmentHeight;

        Point A = *pts[0] + (*pts[2] - *pts[0]) * alpha;
        Point B = secondHalf ? *pts[1] + (*pts[2] - *pts[1]) * beta : *pts[0] + (*pts[1] - *pts[0]) * beta;

        if (A.getX() > B.getX())
            std::swap(A, B);

        int start_x = std::min(maxX, std::max(static_cast<int>(A.getX()), minX));
        int end_x = std::max(minX, std::min(static_cast<int>(B.getX()), maxX));

        int x = start_x;
        double phi = (A.getX() == B.getX()) ? 1.0 : static_cast<double>(x - A.getX()) / (B.getX() - A.getX());
        double z = A.getZ() + (B.getZ() - A.getZ()) * phi;



        for (int x = start_x + 1 ; x < end_x - 1; ++x)
        {
            phi = (A.getX() == B.getX()) ? 1.0 : static_cast<double>(x - A.getX()) / (B.getX() - A.getX());
            z = A.getZ() + (B.getZ() - A.getZ()) * phi;

            if (z < z_buffer[y][x])
            {
                z_buffer[y][x] = z;
            }
        }
    }
}


void QtDrawer::drawLineWithZBuffer(const Point &p1, const Point &p2) {
    int x0 = static_cast<int>(p1.getX());
    int y0 = static_cast<int>(p1.getY());
    int x1 = static_cast<int>(p2.getX());
    int y1 = static_cast<int>(p2.getY());
    double z0 = p1.getZ();
    double z1 = p2.getZ();

    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
        std::swap(z0, z1);
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    double dz = (z1 - z0) / dx;

    int error = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;
    double z = z0;
    Point start_point(x0, y0, z0);
    Point end_point(x0,y0, z0);
    if (steep)
    {
        start_point = Point(y0, x0, z0);
        end_point = Point(y0,x0, z0);

    }
    for (int x = x0; x <= x1; ++x)
    {
        if (steep)
        {
            if (isInBounds(y, x) && z <= z_buffer[x][y] + 5)
            {
                z_buffer[x][y] = z;
                drawPoint(y,x);
            }
        }
        else
        {
            if (isInBounds(x, y) && z <= z_buffer[y][x] + 5)
            {
                z_buffer[y][x] = z;
                drawPoint(x,y);
            }
        }
        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
        z += dz;
    }
}

void QtDrawer::fillLineZbuffer(const Point &p1, const Point &p2)
{
    int x0 = static_cast<int>(p1.getX());
    int y0 = static_cast<int>(p1.getY());
    int x1 = static_cast<int>(p2.getX());
    int y1 = static_cast<int>(p2.getY());
    double z0 = p1.getZ();
    double z1 = p2.getZ();

    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
        std::swap(z0, z1);
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    double dz = (z1 - z0) / dx;

    int error = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;
    double z = z0;
    Point start_point(x0, y0, z0);
    Point end_point(x0,y0, z0);
    if (steep)
    {
        start_point = Point(y0, x0, z0);
        end_point = Point(y0,x0, z0);

    }
    for (int x = x0; x <= x1; ++x)
    {
        if (steep)
        {
            if (isInBounds(y, x) && z <= z_buffer[x][y] + 1)
            {
                z_buffer[x][y] = z;
            }
        }
        else
        {
            if (isInBounds(x, y) && z <= z_buffer[y][x] + 1)
            {
                z_buffer[y][x] = z;
            }
        }
        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
        z += dz;
    }
}

