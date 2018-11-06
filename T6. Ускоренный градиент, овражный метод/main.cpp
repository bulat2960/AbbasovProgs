#include <iostream>
#include <cmath>

using namespace std;

double f(double x1, double x2)
{
	return x1 * x1 + x2 * x2 - cos((x1 - x2) / 2);
}

double df_dx1(double x1, double x2)
{
    return 2 * x1 + 0.5 * sin((x1 - x2) / 2);
}

double df_dx2(double x1, double x2)
{
    return 2 * x2 - 0.5 * sin((x1 - x2) / 2);
}

double norma(double x1, double x2)
{
    return sqrt(pow(x1, 2) + pow(x2, 2));
}

double funcForOneDimMinimize1(double x1, double x2, double alpha)
{
    return f(x1 - alpha * df_dx1(x1, x2), x2 - alpha * df_dx2(x1, x2));
}

double funcForOneDimMinimize2(pair<double, double> x, pair<double, double> y, double alpha)
{
    return f(x.first + alpha * (y.first - x.first), x.second + alpha * (y.second - x.second));
}

double dichotomy1(double a, double b, const double E, double x1, double x2)
{
    const double delta = E / 10;
    double c = (a + b - delta) / 2;
    double d = (a + b + delta) / 2;

    while (b - a > 2 * E)
    {
        double resultC = funcForOneDimMinimize1(x1, x2, c);
        double resultD = funcForOneDimMinimize1(x1, x2, d);
        resultC < resultD ? b = d : a = c;
        c = (a + b - delta) / 2;
        d = (a + b + delta) / 2;
    }

    double resultPoint = (a + b) / 2;
    return resultPoint;
}

double dichotomy2(double a, double b, const double E, pair<double, double> x, pair<double, double> y)
{
    const double delta = E / 100;
    double c = (a + b - delta) / 2;
    double d = (a + b + delta) / 2;

    while (b - a > 2 * E)
    {
        double resultC = funcForOneDimMinimize2(x, y, c);
        double resultD = funcForOneDimMinimize2(x, y, d);
        resultC < resultD ? b = d : a = c;
        c = (a + b - delta) / 2;
        d = (a + b + delta) / 2;
    }

    return (c + d) / 2;
}

pair<double, double> greatDescentTwoIter(double x01, double x02, double eps)
{
    double x1 = x01;
    double x2 = x02;

    double px1 = x1;
    double px2 = x2;

    for (int i = 0; i < 2; i++)
    {
        double alpha = dichotomy1(-1000, 1000, eps / 1000, x1, x2);
        x1 -= alpha * df_dx1(px1, px2);
        x2 -= alpha * df_dx2(px1, px2);

        if (norma(x1 - px1, x2 - px2) < eps)
        {
            break;
        }

        px1 = x1;
        px2 = x2;
    }
    return {x1, x2};
}

pair<double, double> greatDescentOneIter(double x01, double x02, double eps)
{
    double x1 = x01;
    double x2 = x02;

    double px1 = x1;
    double px2 = x2;

    for (int i = 0; i < 1; i++)
    {
        double alpha = dichotomy1(-1000, 1000, eps / 1000, x1, x2);
        x1 -= alpha * df_dx1(px1, px2);
        x2 -= alpha * df_dx2(px1, px2);

        if (norma(x1 - px1, x2 - px2) < eps)
        {
            break;
        }

        px1 = x1;
        px2 = x2;
    }
    return {x1, x2};
}

double fastGradientDescent(double x01, double x02, const double E)
{
    double x1 = x01;
    double x2 = x02;

    int it = 1;

    while (true)
    {
        pair<double, double> yk = greatDescentTwoIter(x1, x2, E / 10);
        pair<double, double> Y0minusX0 = {yk.first - x1, yk.second - x2};
        double optAlpha = dichotomy2(-1000, 1000, E / 10, {x1, x2}, {yk.first, yk.second});

        x1 += Y0minusX0.first * optAlpha;
        x2 += Y0minusX0.second * optAlpha;

        cout << "it = " << it++ << endl;
        cout << "[y1, y2] = [" << yk.first << ", " << yk.second << "]" << endl;
        cout << "[x1, x2] = [" << x1 << ", " << x2 << "]" << endl;
        cout << "[yk - xk] = [" << (Y0minusX0.first - x1) << ", " << (Y0minusX0.second - x2) << "]" << endl;
        cout << "f(x1, x2) = " << f(x1, x2) << endl;

        if (norma(df_dx1(x1, x2), df_dx2(x1, x2)) <= E)
        {
            break;
        }
    }
    return f(x1, x2);
}

double ovragMethod(double x1, double x2, const double E)
{
    int it = 1;

    while (true)
    {
        double xVolna1 = x1 * 1.1;
        double xVolna2 = x2 * 1.1;

        pair<double, double> y = greatDescentOneIter(x1, x2, E / 10);
        pair<double, double> yVolna = greatDescentOneIter(xVolna1, xVolna2, E / 10);

        double optAlpha = dichotomy2(-1000, 1000, E / 100, y, yVolna);

        x1 = y.first + optAlpha * (yVolna.first - y.first);
        x2 = y.second + optAlpha * (yVolna.second - y.second);

        cout << "it = " << it++ << endl;
        cout << "[x1, x2] = [" << x1 << ", " << x2 << "]" << endl;
        cout << "optAlpha = " << optAlpha << endl;

        if (norma(df_dx1(x1, x2), df_dx2(x1, x2)) <= E)
        {
            break;
        }
    }
    return f(x1, x2);
}

int main()
{
    double x1 = 2;
    double x2 = -1;
    const double E = 0.0005;

    cout << "FAST GRADIENT DESCENT" << endl;
    double value1 = fastGradientDescent(x1, x2, E);
    cout << "Func min value = " << value1 << endl;

    cout << "OVRAG METHOD" << endl;
    double value2 = ovragMethod(x1, x2, E);
    cout << "Func min value = " << value2 << endl;

    return 0;
}
