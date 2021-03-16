#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Function
{
public:
    virtual int getK() = 0;
    virtual double getf(vector<double> x) = 0;
};

class function2 : public Function
{
public:
    int getK()override;
    double getf(vector<double> x) override;
};

class function3 : public Function
{
public:
    int getK()override;
    double getf(vector<double> x) override;
};


