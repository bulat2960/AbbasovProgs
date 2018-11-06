#include <iostream>
#include <cmath>

using namespace std;

inline double funcValue(double x)
{
    return sqrt(1 + x * x) + exp(-2 * x);
}

inline double derivValue(double x) // Proizvodnaya
{
    return (x / sqrt(1 + x * x)) - 2 * exp(-2 * x);
}

double hordsMethod(double x0, double E)
{
    double xMemory0 = x0;
    double xMemory1 = x0 + 1;

    int it = 0;
    double x;
    while (true)
    {
        x = xMemory1 - (xMemory1 - xMemory0) * derivValue(xMemory1) / (derivValue(xMemory1) - derivValue(xMemory0));

        cout << "it = " << ++it << endl;
        cout << "x = " << x << endl;

        if (abs(derivValue(x)) < E)
        {
            break;
        }

        xMemory0 = xMemory1;
        xMemory1 = x;
    }
    cout << it << " iterations" << endl;
    return x;
}

/* ------------------------------------------------------- */

double f(double x1, double x2)
{
	return x1 * x1 + x2 * x2 - cos((x1 - x2) / 2);
}

double passiveSearch(double x1, double x2, double a, double b, const double E, int step)
{
    int n = floor((b - a) / E) + 1;

    double pointArray[n];
    pointArray[0] = a;
    for (int i = 1; i < n; i++)
    {
        pointArray[i] = pointArray[i - 1] + E;
    }

    double minFunc = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        double result;
        if (step % 2 == 1)
        {
            result = f(pointArray[i], x2);
        }
        else
        {
            result = f(x1, pointArray[i]);
        }

        if (result < minFunc)
        {
            minFunc = result;
        }
        else
        {
            return pointArray[i - 1];
        }
    }
}

double norm(double x11, double x12, double x21, double x22)
{
    return sqrt(pow((x21 - x11), 2) + pow((x22 - x12), 2));
}

double coordDescent(double x01, double x02, const double E)
{
    double x1 = x01;
    double x2 = x02;

    /* (step % 2 == 1) x1 -> min : else x2 -> min */
    int step = 0;
    while (true)
    {
        step++;
        double value = passiveSearch(x1, x2, -100, 100, E, step);

        if (step % 2 == 1)
        {
            if (norm(value, x2, x1, x2) <= E)
            {
                return f(value, x2);
            }
            else
            {
                x1 = value;
            }
        }
        else
        {
            if (norm(x1, value, x1, x2) <= E)
            {
                return f(x1, value);
            }
            else
            {
                x2 = value;
            }
        }

        cout << "it = " << step << endl;
        cout << "[x1, x2] = [" << x1 << ", " << x2 << "]" << endl;
        cout << "f = " << f(x1, x2) << endl;
    }
}

int main()
{
    const double E = 0.1;
    double x0 = -2;

    cout << "HORDS METHOD" << endl;
    double value = hordsMethod(x0, E);
    cout << "Func min value = " << funcValue(value) << endl;

    cout << endl;

    double x1 = 5;
    double x2 = 5;

    cout << "COORD DESCENT" << endl;
    double fValue = coordDescent(x1, x2, E);
    cout << "Func min value = " << fValue << endl;


    return 0;
}
