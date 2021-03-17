#include <iostream>
#include <cmath>
#include <vector>
#include "optimisation.h"
#include <algorithm>
#include "Area.h"
#include "function.h"
#include <random>
mt19937 generator;
using namespace std;

    int Optimisation::getIter() 
    { 
        return iter; 
      }

    int Optimisation::getSize()
    {
        return vecX.size();
    }

    vector<double> Optimisation::getRez()
    {
        return vecX.back();
    }

    double Optimisation::getVecX(int i, int j)
    {
        return vecX[i][j];
    }

  

    void  Newton:: matByRow(vector<vector<double>>& mat, const vector<double>& vec, vector<double>& p, int n)
    {
        double sum = 0;
        for (int i = 0; i < n; ++i)
        {
            sum = 0;
            for (int j = 0; j < n; ++j)
            {
                sum += mat[i][j] * vec[j];
            }
            p.push_back(-sum);
        }
    }
    vector<double> Newton::calcP(Function& f, int ind)
    {
        if (!invMatr.empty())
        {
            invMatr.clear();
  }
        int n = f.getK();
        vector<double> temp(n, 0);
        for (int j = 0; j < n; ++j)
        {
            invMatr.push_back(temp);
            invMatr[j][j] = 1;
        }

        inverse(getHessian(), invMatr, n);
        if (!p.empty())
        {
            p.clear();
        }
        
        matByRow(invMatr, getGradient(), p, n);

        invMatr.clear();
        return p;
    }

    double  Newton::getNorma( const vector<double>& x, int n)
    {
        double norm = 0;
        for (int i = 0; i < n; ++i)
        {
            norm += x[i] * x[i];
        }
        norm = sqrt(norm);
        return norm;
    }

    double Newton::getNorma(double x) 
    {
        return abs(x);
    }

    bool Newton:: Stop( Function& f,  int stopCrit, int maxIter)
    {
        int size = f.getK();

          if (!temp.empty())
        {
            temp.clear();
        }
        
          switch (stopCrit)
          {
          case 1:
              if ((getNorma(getGradient(), size) < eps )|| (iter >= maxIter))
                  return false;
              break;
          case 2:
              if (iter > 0)
              {
                  
                  for (int i = 0; i < size; ++i)
                  {
                      temp.push_back(vecX[iter][i] - vecX[iter - 1][i]);
                      
                  }
                  
                  if ((getNorma(temp, size) < eps)|| (iter >= maxIter))
                  {
                      return false;
                  }
              }
              break;
          default:
              if (iter > 0)
              {
                  if ((getNorma((f.getf(vecX[iter]) - f.getf(vecX[iter - 1])) / f.getf(vecX[iter])) < eps)|| (iter >= maxIter))
                  {
                    return false;
                  }
              }
              break;
              
      
            
          }
       
        return true;
    }

    void Newton:: calcOptim(vector<double>& x, Function& f, Area areaOpt, int stopCrit ,double eps,int maxIter)
    {
        vecX.push_back(x);
        int n = f.getK();
        vector <double> tempP(n, 0), tempX(n,0);
        double alpha = 2;
        calcGradient(f,x );

        calcHessian(f, x);
        for (iter = 0; Stop( f,stopCrit, maxIter); ++iter, alpha /= 2)
        {
            tempP = calcP(f,iter);
            for (int j = 0; j < n; ++j)
            {
               
                tempX[j] = vecX[iter][j] + tempP[j] * alpha;
                
             
            }
            vecX.push_back(tempX);
            areaOpt.chekArea(vecX, iter,n);

            calcGradient(f, vecX[iter+1]);

            calcHessian(f, vecX[iter+1]);
            
          

        }
        invMatr.clear();
    }

    vector<double> Newton::getRez()
    {
        return vecX.back();
    }

    void Newton::calcGradient(Function& f, vector<double>& x)
    {
        double rtemp, ltemp;
        if (!gradient.empty())
        {
            gradient.clear();
        }
        for (int i = 0; i < f.getK(); ++i)
        {
            x[i] -= eps;
            ltemp = f.getf(x);
            x[i] += 2 * eps;
            rtemp = f.getf(x);
            gradient.push_back((rtemp - ltemp) / (2 * eps));
            x[i] -= eps;

        }
    }
    void Newton::calcHessian(Function& f, vector<double> &x)
    {
        double ftemp1, ftemp2, ftemp3;
        if (!hessian.empty())
        {
            hessian.clear();
        }
        vector<double> vectemp(f.getK(), 0);
        for (int i = 0; i < f.getK(); ++i)
        {
            for (int j = 0; j < f.getK(); ++j)
            {
                x[i] += eps;
                ftemp1 = f.getf(x);
                x[j] += eps;
                ftemp3 = f.getf(x);
                x[i] -= eps;
                ftemp2 = f.getf(x);
                x[j] -= eps;
                vectemp[j] = (ftemp3 - ftemp2 - ftemp1 + f.getf(x)) / (eps * eps);
            }
            hessian.push_back(vectemp);
        }
       

    }
   
    vector<vector<double>>  Newton::getHessian()
    {
        return hessian;
    }
    vector<double>  Newton::getGradient()
    {
        return gradient;
    }


    void gauseforward(vector<vector<double>>& b, vector<vector<double>>& a, int n, int k)
    {
        int j, i;
        double temp = a[k][k];
        for (i = 0; (i < n) && (a[k][k] != 0); ++i)
        {
            b[k][i] = b[k][i] / temp;
            a[k][i] = a[k][i] / temp;
        }
        for (i = k + 1; i < n; i++) {
            double cur = a[i][k];
            for (j = 0; j < n; j++)
            {
                b[i][j] = b[i][j] - cur * b[k][j];
                a[i][j] = a[i][j] - cur * a[k][j];
            }
        }
        
    }


    void gauseback(vector<vector<double>>& b, vector<vector<double>>& a, int n, int k)
    {
        int j, i;
        double temp = a[k][k];
        for (i = n - 1; (i >= 0) && (a[k][k] != 0); --i)
        {
            b[k][i] = b[k][i] / temp;
            a[k][i] = a[k][i] / temp;
        }
        for (i = k - 1; i >= 0; i--)
        {
            double cur = a[i][k];
            for (j = n - 1; j >= 0; j--)
            {
                b[i][j] = b[i][j] - cur * b[k][j];
                a[i][j] = a[i][j] - cur * a[k][j];
            }
        }
        
    }

    void inverse(const vector<vector<double>>& a, vector<vector<double>>& b, int n)
    {
        vector<vector<double>> temp(a);
       
        for (int i = 0; i < n; ++i)
        {
            gauseforward(b, temp, n, i);
           
        }

        for (int i = n - 1; i >= 0; --i)
            gauseback(b, temp, n, i);

    }


    void RandomSearch::calcOptim(vector<double>& x, Function& f, Area areaOpt, int stopCrit, double epsN, int maxIter)
    {

        eps = epsN;
        
        vecX.push_back(x);
        int n = f.getK();
        uniform_real_distribution<> dist(0.,1.);
        double alpha;
        vector<double> tempX(n, 0);
        for (int i = 0; i < n; ++i)
        {
            alpha = dist(generator);
            tempX[i] = areaOpt.getFirst()[i] + alpha * (areaOpt.getSecond()[i] - areaOpt.getFirst()[i]);
        }
       
        
        

        for (iter = 0; Stop(f, stopCrit,maxIter); ++iter)
        {
            if (f.getf(tempX) > f.getf(vecX.back()))
            {
               
                
                for (int i = 0; i < n; ++i)
                {
                    alpha = dist(generator);
                    tempX[i] = areaOpt.getFirst()[i] + alpha * (areaOpt.getSecond()[i] - areaOpt.getFirst()[i]);
                }
                
                
            }
            else
            {
                cout << "in:" << tempX[0] << " " << tempX[1] << endl;
                vecX.push_back(tempX);
                for (int i = 0; i < n; ++i)
                {
                    alpha = dist(generator);
                    tempX[i] = areaOpt.getFirst()[i] + alpha * (areaOpt.getSecond()[i] - areaOpt.getFirst()[i]);
                }
                lastOptim = iter;
            }
            
        }
        
    }
    bool RandomSearch::Stop(Function& f,  int stopCrit, int maxIter)
    {
        

        
       if (( (iter-lastOptim)> 3) || (iter >= maxIter))
                return false;
        
 
      

        return true;
    }