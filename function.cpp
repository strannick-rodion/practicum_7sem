#include "function.h"



using namespace std;

int function2::getK()
{
    return  2;
}

double function2::getf(vector<double> x)
{
    return (x[1] - 3) * (x[1] - 3) + (x[0] + 5) * (x[0] + 5) - 3;
}

int function3::getK()
{
    return  3;
}

double function3::getf(vector<double> x)
{
    return x[1] * x[1] + x[2] * x[2] + x[0] * x[0] + 5;
}