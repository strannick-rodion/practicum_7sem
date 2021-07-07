#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Area
{
    vector <double> first;
    vector <double> second;

public:
    Area( vector<double>& a,  vector<double>& b);
    Area();

    bool inArea(const vector<double>& x);

    void chekArea(vector<vector<double>>& x, int ind ,int n);

    vector<double> getFirst();
    vector<double> getSecond();
    void setArea(vector<double>a, vector<double>b);
};
