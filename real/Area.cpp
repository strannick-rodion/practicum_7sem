#include "Area.h"


using namespace std;

Area::Area(vector<double>& a, vector<double>& b) : first(a), second(b) {};
Area::Area()
{
    first={0};
    second={0};
};

vector<double> Area::getFirst() { return first; }
vector<double>Area::getSecond() { return second; }
bool Area::inArea(const vector<double>& x)
{
    bool res = true;
    for (int i = 0; (i < x.size()) && res; ++i)
    {
        res = (x[i] >= first[i]) && (x[i] <= second[i]);
    }
    return res;
}
void Area::chekArea(vector<vector<double>>& x, int ind, int n) 
{
    double temp, p, minDist, a,b;
    if (!inArea(x[ind + 1]))
    {
        p = x[ind + 1][0] - x[ind][0];
        a = (first[0] - x[ind][0]) / p;
        b = (second[0] - x[ind][0]) / p;
        minDist = max(a,b);

        for (int i = 1; i < n; ++i)
        {
            p = x[ind + 1][i] - x[ind][i];

            a = (first[i] - x[ind][i]) / p;
            b = (second[i] - x[ind][i]) / p;
            temp = max(a, b);
            minDist = min(minDist, temp);

        }
        for (int i = 0; i < n; ++i)
        {
            p = x[ind + 1][i] - x[ind][i];
            x[ind + 1][i] = x[ind][i] + p * minDist;

        }
    }
}
void Area::setArea(vector<double>a, vector<double>b)
{
    first = a;
    second = b;
}
