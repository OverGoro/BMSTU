#include "../headers/menu.hpp"

#include "points.hpp"
#include "ermit.hpp"
#include "newton.hpp"

#define EPS 1e-6

void print_menu()
{
    std::cout << "0) Выйти\n";
    std::cout << "1) Получить таблицу значений y(x) для ряда степеней полиномов Ньютона и Эрмита, при фиксированном x \n";
    std::cout << "2) Найти корень табличной функции\n";
    std::cout << "3) Решить систему из 2 нелинейных уравнений\n";
    std::cout << "Введите команду: ";
}

int get_command(int &command)
{
    if (!(std::cin >> command))
    {
        std::cin.clear(); // Сброс флагов ошибки ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода до символа новой строки
        return ERR_IO;
    }
    return OK;
}

static void replace_null_derivatives(std::vector<std::vector<double>> &points)
{

    ErmitPolynome ep;
    for (size_t i = 0; i < points.size(); i++)
    {
        // Если первая производная равна 0
        if (points[i][2] == 0)
        {        
            ep.form(points, points[i][0], 2);
            points[i][0] += EPS;
            double old_y = points[i][1];
            double old_dy = points[i][2];
            points[i][1] = ep.count(points[i][0]);
            points[i][2] = (points[i][1] - old_y) / EPS;
            if (points[i].size() > 3)
            {
                points[i][3] = (points[i][2] - old_dy) / EPS;
                points[i].resize(4);
            }
        }
    }
}

int command_get_table()
{
    char filename[] = "data.txt";
    std::vector<std::vector<double>> points;
    int rc = points_read(points, filename);

    size_t max_n = 0;
    double x = 0;

    std::cout << "Максимальное количество точек: ";
    if (!(std::cin >> max_n))
        rc = ERR_IO;


    std::cout << "Точка: ";
    if (!(std::cin >> x))
        rc = ERR_IO;

    ErmitPolynome ep;
    NewtonPolynome np;
    for (size_t i = 1; !rc && i < max_n; i++)
    {
        rc = ep.form(points, x, i);
        if (!rc)
            rc = np.form(points, x, i);
        if (!rc)
        {
            std::cout << "Количество точек: " << i << "\n";
            double n_y = np.count(x);
            double e_y = ep.count(x);
            std::cout << "Полином Ньютона: " << n_y << "\n";
            std::cout << "Полином Эрмита: " << e_y << "\n\n";
        }
    }
    
    
    return rc;
}

int command_get_root()
{
    char filename[] = "test";
    std::vector<std::vector<double>> points;
    int rc = points_read(points, filename);
    if (!rc) 
    {
        replace_null_derivatives(points);
        points_inverse(points);
        // points_sort_by_x(points);
    }

    size_t max_n = 0;

    std::cout << "Максимальное количество точек: ";
    if (!(std::cin >> max_n))
        rc = ERR_IO;

    // points_print(points);

    ErmitPolynome ep;
    NewtonPolynome np;
    if (!rc)
        rc = np.form(points, 0, max_n);
    if (!rc)
        rc = ep.form(points, 0, max_n);
    if (!rc)
    {
        // np.print();
        // ep.print();
        std::cout << "Результат полинома Ньютона: " << np.count(0) << "\n";
        std::cout << "Результат полинома Эрмита: " << ep.count(0) << "\n";
    }
    return rc;
}

int command_solve_system()
{
    char filename_1[] = "data_1.txt";
    char filename_2[] = "data_2.txt";

    std::vector<std::vector<double>> inp_points_1, inp_points_2, dif_points;

    int rc = points_read(inp_points_1, filename_1);
    if (!rc)
        rc = points_read(inp_points_2, filename_2);
    if (!rc) 
        points_inverse(inp_points_1);

    size_t max_n = 0;

    std::cout << "Максимальное количество точек: ";
    if (!(std::cin >> max_n))
        rc = ERR_IO;

    NewtonPolynome np;

    dif_points.resize(inp_points_1.size());
    for (size_t i = 0; !rc && i < dif_points.size(); i++)
    {
        rc = np.form(inp_points_2, inp_points_1[i][0], max_n);
        if (!rc)
        {
            dif_points[i].resize(2);
            dif_points[i][0] = inp_points_1[i][0];        
            dif_points[i][1] = inp_points_1[i][1] - np.count(dif_points[i][0]);
        }
    }

    points_inverse(dif_points);
    //points_sort_by_x(dif_points);
    points_print(dif_points);
    if (!rc)
        rc = np.form(dif_points, 0, max_n);
    if (!rc)
    {
        np.print();
        double x = np.count(0);
        std::cout << "Результат полинома Ньютона: \n x = " << x << "\n";
        np.form(inp_points_1, x, max_n);
        std::cout << "y = " << np.count(x) << "\n";
    }
    return rc;
}
