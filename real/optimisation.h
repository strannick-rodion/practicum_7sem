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
    Optimisation(){};
    int getIter();
    vector<vector<double>> getVecX();
    vector<double> getRez();
    virtual void calcOptim(vector<double>& x, Function& f, Area areaOpt, int stopCrit, double eps)=0;
    virtual bool Stop(Function& f,  int topCrit)=0;
};


class RandomSearch:public Optimisation
{
    int lastOptim=0;
public:
    RandomSearch(): Optimisation(){};
    void calcOptim(vector<double>& x, Function& f, Area areaOpt, int stopCrit, double eps)override;
    bool Stop(Function& f,  int topCrit)override;
};


class Newton:public Optimisation
{

    vector<double> p, temp;
    vector<vector<double>> invMatr;
    vector<double> gradient;
    vector < vector <double> > hessian;
 
public:
    Newton(): Optimisation(){};
    void matByRow(vector<vector<double>>& mat, const vector<double>& vec, vector<double>& p, int n);
    vector<double> calcP(Function& f, int ind);

    double getNorma( const vector<double>& x, int n);
    double getNorma(double x);
    void calcGradient(Function& f, vector<double>& x);
    void calcHessian(Function& f, vector<double>&x);
    vector<vector<double>> getHessian();
    vector<double> getGradient();
    bool Stop( Function& f,  int topCrit);

    void calcOptim(vector<double>& x, Function& f, Area areaOpt, int stopCrit, double eps)override;

    vector<double> getRez();
};

void gauseforward(vector<vector<double>>& b, vector<vector<double>>& a, int n, int k);
void gauseback(vector<vector<double>>& b, vector<vector<double>>& a, int n, int k);
void inverse(const vector<vector<double>>& a, vector<vector<double>>& b, int n);
