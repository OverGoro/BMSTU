#include <spline.hpp>

double Spline::fi(const Spline &ps) const
{
    return 3 * ((y_1 - y_0) / h - (y_0 - ps.y_0) / ps.h);
}

void Spline::set_Xi(const Spline &pps, const Spline &ps)
{
    Xi = - (ps.h) / (pps.h * ps.Xi + 2 * (pps.h + ps.h));
}

void Spline::set_Xi(double xi)
{
    this->Xi = xi;
}

void Spline::set_Nu(const Spline &pps, const Spline &ps)
{
    Nu = (ps.fi(pps) - pps.h * ps.Nu) / (pps.h * ps.Xi + 2 * (pps.h + ps.h));
}

void Spline::set_Nu(double nu)
{
    this->Nu = nu;
}

void Spline::set_b()
{
    b = (y_1 - y_0) / h - h * (2 * c) / 3;
}

void Spline::set_b(const Spline &next_spline)
{
    b = (y_1 - y_0) / h - (h * (next_spline.c + 2 * c)) / 3;
}

void Spline::set_c(const Spline &next_spline)
{
    c = next_spline.Xi * next_spline.c + next_spline.Nu;
}
void Spline::set_c(double c)
{
    this->c = c;
}

void Spline::set_d()
{
    d = -c / 3 / h;
}

void Spline::set_d(const Spline &next_spline)
{
    d = (next_spline.c - c) / 3 / h;
}

Spline::Spline()
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    x_0 = 0;
    x_1 = 0;
    y_0 = 0;
    y_1 = 0;
    Nu = 0;
    Xi = 0;
}

Spline::~Spline()
{
}

Spline::Spline(double x_0, double y_0, double x_1, double y_1)
{
    a = y_0;
    b = 0;
    c = 0;
    d = 0;

    this->x_0 = x_0;
    this->x_1 = x_1;

    this->y_0 = y_0;
    this->y_1 = y_1;

    h = x_1 - x_0;
    Nu = 0;
    Xi = 0;
}

void Spline::print() const
{
    std::cout << "Сплайн\n";
    std::cout << "A: " << a << "\nB: " << b << "\nC: " << c << "\nD: " << d << "\n";
    std::cout << "Xi: " << Xi << "\n";
    std::cout << "Nu: " << Nu << "\n";
    std::cout << "h: " << h << "\n";
    std::cout << "Point_1: " << x_0 << "\t" << y_0 << "\n";
    std::cout << "Point_2: " << x_1 << "\t" << y_1 << "\n\n";
}

double Spline::operator()(double x) const
{
    double res = a;

    double cur_x = x - x_0;
    res += b * cur_x;

    cur_x *= (x - x_0);
    res += c * cur_x;

    cur_x *= (x - x_0);
    res += d * cur_x;

    return res;
}

bool Spline::contain_x(double x) const
{
    if (x >= x_0 && x <= x_1)
        return true;
    return false;
}

void Spline::print_splines(const std::vector<Spline> &splines)
{
    for (auto s : splines)
        s.print();
}

std::vector<Spline> Spline::generate_splines(std::vector<double> &x, std::vector<double> &y)
{
    std::vector<Spline> splines;
    if (x.size() < 2 || y.size() < 1 || x.size() != y.size())
        return splines;
    
    Spline extra_spline; // Дополнительный сплайн в конце для нахождения С

    // Создание сплайнов по точкам + Заполнение а
    for (int i = 1; i < x.size(); i++)
        splines.push_back(Spline(x[i - 1], y[i - 1], x[i], y[i]));
    
    // C N+1 = 0 C1 = 0
    extra_spline.set_c(0);
    splines[0].set_c(0);

    // Xi[2] = 0 Nu[2] = 0
    splines[1].set_Xi(0);
    splines[1].set_Nu(0);

    // Вычисление Xi, Nu
    for (int i = 2; i < splines.size(); i++)
    {
        splines[i].set_Xi(splines[i - 2], splines[i - 1]);
        splines[i].set_Nu(splines[i - 2], splines[i - 1]);
    }
    extra_spline.set_Xi(splines[splines.size() - 2], splines[splines.size() - 1]);
    extra_spline.set_Nu(splines[splines.size() - 2], splines[splines.size() - 1]);

    // Установка С в N сплайне
    splines[splines.size() - 1].set_c(extra_spline);

    // Установка остальных С
    for (int i = splines.size() - 2; i >= 0; i--)
        splines[i].set_c(splines[i + 1]);

    // Установка b,d
    for (int i = 0; i < splines.size() - 1; i++)
    {
        splines[i].set_b(splines[i + 1]);
        splines[i].set_d(splines[i + 1]);
    }
    splines[splines.size() - 1].set_b();
    splines[splines.size() - 1].set_d();

    return splines;
}

std::vector<Spline> Spline::generate_splines_1(std::vector<double> &x, std::vector<double> &y)
{
    std::vector<Spline> splines;
    if (x.size() < 2 || y.size() < 1 || x.size() != y.size())
        return splines;
    
    Spline extra_spline; // Дополнительный сплайн в конце для нахождения С

    // Создание сплайнов по точкам + Заполнение а
    for (int i = 1; i < x.size(); i++)
        splines.push_back(Spline(x[i - 1], y[i - 1], x[i], y[i]));
    
    // C N+1 = 0 C1 = 0
    extra_spline.set_c(0);
    splines[0].set_c(0);

    // Xi[2] = 0 Nu[2] = 0
    splines[1].set_Xi(0);
    splines[1].set_Nu(0);

    // Вычисление Xi, Nu
    for (int i = 2; i < splines.size(); i++)
    {
        splines[i].set_Xi(splines[i - 2], splines[i - 1]);
        splines[i].set_Nu(splines[i - 2], splines[i - 1]);
    }
    extra_spline.set_Xi(splines[splines.size() - 2], splines[splines.size() - 1]);
    extra_spline.set_Nu(splines[splines.size() - 2], splines[splines.size() - 1]);

    // Установка С в N сплайне
    splines[splines.size() - 1].set_c(extra_spline);

    // Установка остальных С
    for (int i = splines.size() - 2; i >= 0; i--)
        splines[i].set_c(splines[i + 1]);

    // Установка b,d
    for (int i = 0; i < splines.size() - 1; i++)
    {
        splines[i].set_b(splines[i + 1]);
        splines[i].set_d(splines[i + 1]);
    }
    splines[splines.size() - 1].set_b();
    splines[splines.size() - 1].set_d();

    return splines;
}

std::vector<Spline> Spline::read_splines(std::string filename)
{
    // Открываем файл для чтения
    std::ifstream infile(filename);

    if (!infile.is_open())
    {
        // Если не удалось открыть файл, выводим сообщение об ошибке
        std::cerr << "Ошибка: Не удалось открыть файл для чтения\n";
        return std::vector<Spline>();
    }

    double value_x, value_y;
    std::vector<double> x, y;

    // Считываем значения из файла и добавляем их в соответствующие массивы
    while (infile >> value_x >> value_y)
    {
        x.push_back(value_x);
        y.push_back(value_y);
    }

    // Закрываем файл
    infile.close();

    return generate_splines(x, y);
}

void Spline::print_values_splines(const std::vector<Spline> &splines, double x_0, double x_1, double step, std::string filename)
{
    if (x_1 < x_0)
        std::swap(x_1, x_0);
    if (step < 0)
        step = std::abs(step);
    else if (step == 0)
    {
        std::cerr << "Нулевой шаг\n";
        return;
    }

    std::ofstream outfile(filename);

    if (!outfile.is_open())
    {
        std::cerr << "Ошибка: Не удалось открыть файл для записи\n";
        return;
    }

    for (double x = x_0; x < x_1; x += step)
    {
        for (auto spline : splines)
        {
            if (spline.contain_x(x))
            {
                outfile << x << "\t" << spline(x) << "\n";
                break;
            }
        }
    }
    outfile.close();
}
