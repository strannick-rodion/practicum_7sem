#pragma once
#include"Area.h"
#include"function.h"

using namespace std;




class Optimisation
{
protected:
    double eps = 0.01;
    int iter;
    vector<vector<double>> vecX;
public:
    int getIter();
    vector<double> getRez();
    virtual void calcOptim(vector<double>& x, Function& f, Area areaOpt, int stopCrit, double eps, int maxIter) = 0 {};
    virtual bool Stop(Function& f,  int topCrit, int maxIter) = 0 {};
    double getVecX(int i, int j);
    int getSize();
};


class RandomSearch:public Optimisation
{
    int lastOptim=0;
public:

    void calcOptim(vector<double>& x, Function& f, Area areaOpt, int stopCrit, double eps, int maxIter)override;
    bool Stop(Function& f,  int topCrit, int maxIter)override;
};


class Newton:public Optimisation
{
    vector<double> p, temp;
    vector<vector<double>> invMatr;
    vector<double> gradient;
    vector < vector <double> > hessian;
 
public:
    
    void matByRow(vector<vector<double>>& mat, const vector<double>& vec, vector<double>& p, int n);
    vector<double> calcP(Function& f, int ind);

    double getNorma( const vector<double>& x, int n);
    double getNorma(double x);
    void calcGradient(Function& f, vector<double>& x);
    void calcHessian(Function& f, vector<double>&x);
    vector<vector<double>> getHessian();
    vector<double> getGradient();
    bool Stop( Function& f,  int topCrit, int maxIter);

    void calcOptim(vector<double>& x, Function& f, Area areaOpt, int stopCrit, double eps, int maxIter)override;

    vector<double> getRez();
};

void gauseforward(vector<vector<double>>& b, vector<vector<double>>& a, int n, int k);
void gauseback(vector<vector<double>>& b, vector<vector<double>>& a, int n, int k);
void inverse(const vector<vector<double>>& a, vector<vector<double>>& b, int n);
