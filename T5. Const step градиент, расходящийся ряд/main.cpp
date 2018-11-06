#include <iostream>
#include <cmath>

using namespace std;

const int MAX_ITER = 1000;

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

double gradientWithConstStep(double x01, double x02, double eps)
{
    double x1 = x01;
    double x2 = x02;

    int it = 0;

    double px1 = x1;
    double px2 = x2;

    const double step = 0.05;

    while (it++ < MAX_ITER)
    {
        x1 -= step * df_dx1(px1, px2);
        x2 -= step * df_dx2(px1, px2);
        cout << "it = " << it << endl;
        cout << "[x1, x2] = [" << x1 << ", " << x2 << "]" << endl;
        cout << "f(x1, x2) = " << f(x1, x2) << endl << endl;

        if (norma(x1 - px1, x2 - px2) <= eps)
        {
            break;
        }

        px1 = x1;
        px2 = x2;
    }

    cout << it << " iterations" << endl;
    return f(x1, x2);
}

double divergentRow(double x01, double x02, const double eps)
{
    double x1 = x01;
    double x2 = x02;

    int it = 0;

    double px1 = x1;
    double px2 = x2;

    while (it++ < MAX_ITER)
    {
        x1 -= (1.0 / it) * df_dx1(x1, x2);
        x2 -= (1.0 / it) * df_dx2(x1, x2);
        cout << "it = " << it << endl;
        cout << "[x1, x2] = [" << x1 << ", " << x2 << "]" << endl;
        cout << "f(x1, x2) = " << f(x1, x2) << endl << endl;

        cout << norma(x1 - px1, x2 - px2) << ' ' << eps << endl;
        if (norma(x1 - px1, x2 - px2) <= eps)
        {
            break;
        }

        px1 = x1;
        px2 = x2;
    }

    cout << it << " iterations" << endl;
    return f(x1, x2);
}

int main()
{
    const double x1 = 100;
    const double x2 = 100;
    const double E = 0.005;

    cout << "GRADIENT WITH CONST STEP" << endl;
	double opt1 = gradientWithConstStep(x1, x2, E);
	cout << "Func min value = " << opt1 << endl << endl;

	cout << "DIVERGENT ROW" << endl;
	double opt2 = divergentRow(x1, x2, E);
	cout << "Func min value = " << opt2 << endl << endl;
    return 0;
}
