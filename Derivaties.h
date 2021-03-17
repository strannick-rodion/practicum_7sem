#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "function.h"
using namespace std;
class Derivaties
{
protected:
    double eps = 0.1;
    int n = 0;
    vector<double> gradient;
    vector < vector <double> > hessian;

public:
    Derivaties(int k, double epsN) :n(k), eps(epsN) {};
    vector<vector<double>> getHessian();
    vector<double> getGradient();
    int getN();
    void calcGradient(Function& f, vector<double>& x);
    void calcHessian(Function& f, vector<double>x);

};

void gauseforward(vector<vector<double>>& b, vector<vector<double>>& a, int n, int k);
void gauseback(vector<vector<double>>& b, vector<vector<double>>& a, int n, int k);
void inverse(const vector<vector<double>>& a, vector<vector<double>>& b, int n);
