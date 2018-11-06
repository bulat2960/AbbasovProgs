#include <iostream>
#include <cmath>

const int MAX_ITER = 1000;

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

double funcForOneDimMinimize(double x1, double x2, double alpha)
{
    return f(x1 - alpha * df_dx1(x1, x2), x2 - alpha * df_dx2(x1, x2));
}

double dichotomy(double a, double b, const double E, double x1, double x2)
{
    const double delta = E / 10;
    double c = (a + b - delta) / 2;
    double d = (a + b + delta) / 2;

    while (b - a > 2 * E)
    {
        double resultC = funcForOneDimMinimize(x1, x2, c);
        double resultD = funcForOneDimMinimize(x1, x2, d);
        resultC < resultD ? b = d : a = c;
        c = (a + b - delta) / 2;
        d = (a + b + delta) / 2;
    }

    double resultPoint = (c + d) / 2;
    return resultPoint;
}

double getNewLambda(double lambda, double x1, double x2)
{
    const double delta = 0.9;
    const double eps = 0.25;

    double dx1 = df_dx1(x1, x2);
    double dx2 = df_dx2(x1, x2);

    while (f(x1 - lambda * dx1,  x2 - lambda * dx2) > f(x1, x2) - eps * lambda * pow(norma(dx1, dx2), 2))
    {
        lambda *= delta;
    }
    return lambda;
}

double gradientWithPartitions(double x01, double x02, double eps)
{
    double x1 = x01;
    double x2 = x02;

    int it = 0;

    double px1 = x1;
    double px2 = x2;

    while (it++ < MAX_ITER)
    {
        double lambda = 1;
        lambda = getNewLambda(lambda, x1, x2);

        double dx1 = df_dx1(x1, x2);
        double dx2 = df_dx2(x1, x2);

        x1 -= lambda * dx1;
        x2 -= lambda * dx2;
        cout << "it = " << it << endl;
        cout << "lambda = " << lambda << endl;
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

double greatDescent(double x01, double x02, double eps)
{
    double x1 = x01;
    double x2 = x02;

    double px1 = x1;
    double px2 = x2;

    int it = 0;
    while (it++ < MAX_ITER)
    {
        double alpha = dichotomy(0, 1, eps / 1000, x1, x2);
        cout << "alpha = " << alpha << endl;
        x1 -= alpha * df_dx1(px1, px2);
        x2 -= alpha * df_dx2(px1, px2);

        cout << "it = " << it << endl;
        cout << "[x1, x2] = [" << x1 << ", " << x2 << "]" << endl;
        cout << "f(x1, x2) = " << f(x1, x2) << endl << endl;

        if (norma(x1 - px1, x2 - px2) < eps)
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
    const double x1 = 5;
    const double x2 = 5;
    const double E = 0.05;

    cout << "GRADIENT WITH PARTITIONS" << endl;
	double opt1 = gradientWithPartitions(x1, x2, E);
	cout << "Func min value = " << opt1 << endl << endl;

	cout << "GREAT DESCENT METHOD" << endl;
	double opt2 = greatDescent(x1, x2, E);
	cout << "Func min value = " << opt2 << endl << endl;
	return 0;
}
