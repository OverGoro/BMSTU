#ifndef NEWTON_HPP__
#define NEWTON_HPP__

class Newton 
{
private:
    double a, b, c, d; // Коэффициенты полинома ax^3 + bx^2 + cx + d
    
public:
    Newton(double coeff_a, double coeff_b, double coeff_c, double coeff_d) : a(coeff_a), b(coeff_b), c(coeff_c), d(coeff_d) {}
    Newton(double x1, double y1, double x2, double y2, double x3, double y3) 
    {
        a = ((y2 - y1) / (x2 - x1) - (y3 - y2) / (x3 - x2)) / (x3 - x1);
        b = (y2 - y1) / (x2 - x1) - a * (x2 + x1);
        c = y1 - a * x1 * x1 - b * x1;
        d = y1;
    }
    double evaluate(double x) 
    {
        return a * x * x * x + b * x * x + c * x + d;
    }

    double firstDerivative(double x) 
    {
        return 3 * a * x * x + 2 * b * x + c;
    }

    double secondDerivative(double x) 
    {
        return 6 * a * x + 2 * b;
    }
};


#endif
