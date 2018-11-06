#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double PI = 3.1415926;

struct Vector2
{
    double x1;
    double x2;
    Vector2() {}
    Vector2(double x1, double x2) : x1(x1), x2(x2) {}
    Vector2(const Vector2& vecCopy)
    {
        x1 = vecCopy.x1;
        x2 = vecCopy.x2;
    }
    void operator-=(const Vector2& vec)
    {
        x1 -= vec.x1;
        x2 -= vec.x2;
    }
    friend ostream& operator<<(ostream& ost, const Vector2& vec)
    {
        ost << vec.x1 << ' ' << vec.x2;
        return ost;
    }
};

struct GesseMatrix
{
    vector<vector<double>> matrix;
    GesseMatrix(double a11, double a12, double a21, double a22)
    {
        matrix.push_back({a11, a12});
        matrix.push_back({a21, a22});
    }
    friend ostream& operator<<(ostream& ost, const GesseMatrix& gesse)
    {
        ost << gesse.matrix[0][0] << ' ' << gesse.matrix[0][1] << endl
            << gesse.matrix[1][0] << ' ' << gesse.matrix[1][1];
        return ost;
    }
};

Vector2 getProduct(GesseMatrix gesse, Vector2 grad)
{
    double x1 = gesse.matrix[0][0] * grad.x1 + gesse.matrix[0][1] * grad.x2;
    double x2 = gesse.matrix[1][0] * grad.x1 + gesse.matrix[1][1] * grad.x2;
    return Vector2(x1, x2);
}

void flip(GesseMatrix& gesse)
{
    const double E = 0.01;
    for (int i = 0; i < gesse.matrix.size(); i++)
    {
        for (int j = 0; j < gesse.matrix[i].size(); j++)
        {
            if (abs(gesse.matrix[i][j]) > E)
            {
                gesse.matrix[i][j] = 1.0 / gesse.matrix[i][j];
            }
        }
    }
}

double f(double x1, double x2)
{
	return x1 * x1 + x2 * x2 - cos((x1 - x2) * PI / 360);
}

double d1f_dx1(double x1, double x2)
{
    return 2 * x1 + 0.5 * sin((x1 - x2) * PI / 360);
}

double d1f_dx2(double x1, double x2)
{
    return 2 * x2 - 0.5 * sin((x1 - x2) * PI / 360);
}

double d2f_dx1(double x1, double x2)
{
    return 2 + 0.25 * cos((x1 - x2) * PI / 360);
}

double d2f_dx1dx2(double x1, double x2)
{
    return -0.25 * cos((x1 - x2) * PI / 360);
}

double d2f_dx2(double x1, double x2)
{
    return 2 + 0.25 * cos((x1 - x2) * PI / 360);
}

/*double f(double x1, double x2)
{
	return 9 * x1 * x1 + x2 * x2;
}

double d1f_dx1(double x1, double x2)
{
    return 18 * x1;
}

double d1f_dx2(double x1, double x2)
{
    return 2 * x2;
}

double d2f_dx1(double x1, double x2)
{
    return 18;
}

double d2f_dx1dx2(double x1, double x2)
{
    return 0;
}

double d2f_dx2(double x1, double x2)
{
    return 2;
}*/

Vector2 NutonMethod(Vector2 st)
{
    Vector2 result = st;

    for (int i = 0; i < 10; i++)
    {
        cout << "RESULT" << endl << result << endl;
        Vector2 grad(d1f_dx1(result.x1, result.x2), d1f_dx2(result.x1, result.x2));
        cout << "GRAD" << endl << grad << endl;
        GesseMatrix matrix(d2f_dx1(result.x1, result.x2), d2f_dx1dx2(result.x1, result.x2),
                           d2f_dx1dx2(result.x1, result.x2), d2f_dx2(result.x1, result.x2));
        cout << "MATRIX" << endl << matrix << endl;
        flip(matrix);
        cout << "TRANSP MATRIX" << endl << matrix << endl;
        Vector2 product = getProduct(matrix, grad);
        cout << "PROD" << endl << product << endl << endl;
        result -= product;
    }
    return result;
}

/* --------------------------------------------- */

int main()
{
    double x1 = 1;
    double x2 = 1;

    Vector2 result = NutonMethod(Vector2(x1, x2));
    cout << "Func min point: (" << result.x1 << ' ' << result.x2 << ")" << endl;
    cout << "Func min value: " << f(result.x1, result.x2) << endl;
    return 0;
}
