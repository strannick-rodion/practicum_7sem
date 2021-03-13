 // NytonBacktracking.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
using namespace std;

class Function 
{
public:  

    virtual int getK()=0;
    virtual double getf(double* x) = 0;   
    virtual ~Function() {};
};

//class function1: public Function
//{
//    int k; 
//    
//public:
//    int getK()override { return  1; };
//    double getf(double* x) override
//    {
//        return (*x-6)* (*x - 6);
//    };
//};

class function2 : public Function
{
public:
    int getK()override { return  2; };
    double getf(double* x) override
    {
        return (x[1]-3) * (x[1]-3) + (x[0]+5) * (x[0]+5) - 3
    };
};


//class function3 : public Function
//{
//public:
//    int getK()override { return  3; };
//    double getf(double* x) override
//    {
//        return x[1] * x[1] + x[2] * x[2] + x[0] * x[0] + 5;
//    };
//};


class Derivaties 
{
private:
    double eps = 0.1;
    int n =0;
    double* gradient = nullptr;
    double** hessian = nullptr;

public:
    Derivaties(int k, double epsN) 
    {
   
        n = k;
        eps = epsN;
        gradient = new double[n] {0};
        hessian = new double* [n];
        for (int i = 0; i < n; ++i)
            hessian[i] = new double[n] {0};
    }

    double** getHessian()
    {
        return hessian;
    }
    double* getGradient()
    {
        return gradient;
    }

    int getN() 
    {
        return n;
    }
    void calcGradient(Function &f, double* x)
    {
        double rtemp, ltemp;

        for (int i = 0; i < n; ++i)
        {
            x[i] -= eps;
            ltemp = f.getf(x);
            x[i] +=2*eps;
           // cout << " eeeee   " << x[i]<<endl;
            rtemp = f.getf(x);
           // cout << " eeeee   " << rtemp<<endl;
            gradient[i] = (rtemp - ltemp) / (2 * eps);
            x[i] -=eps;
           // cout << "gr=" << gradient[i] << "\n";
        }
    }

    void calcHessian(Function &f, double* x)
    {
        double ftemp1, ftemp2, ftemp3;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                x[i] += eps;
                ftemp1 = f.getf(x);
                x[j] += eps;
                ftemp3 = f.getf(x);
                x[i] -= eps;
                ftemp2 = f.getf(x);
                x[j] -= eps;
                hessian[i][j] = (ftemp3-ftemp2-ftemp1+f.getf(x) )/ (eps * eps);
            }            
        }
        cout << "hessian:" << endl << hessian[0][0] << " " << hessian[0][1] << endl << hessian[1][0] << " " << hessian[1][1] << endl << "__" << endl;
       
    }

    ~Derivaties() 
    {
        if (gradient) {
            delete[] gradient;
        }
        if (hessian)
        {
            for (int i = 0; i < n; ++i)
                delete[] hessian[i];
            delete[] hessian;
        }
    }

};

void gauseforward(double** b, double** a, int n, int k)
{
    int j, i;
    double temp = a[k][k];
    for (i = 0; (i < n) && (a[k][k] != 0); ++i)
    {
        
      //  cout << "akk=" << a[k][k] << endl;
        b[k][i] = b[k][i] / temp;
       // cout << "bki=" << b[k][i]<< endl;
        a[k][i] = a[k][i] / temp;
       // cout << "aki=" << a[k][i] << endl;
    }
    for (i = k + 1; i < n; i++) { 
        double cur = a[i][k];
        for (j = 0; j < n; j++)
        {
            b[i][j] = b[i][j] - cur * b[k][j];
            a[i][j] = a[i][j] - cur * a[k][j];
        }
    }
  //  cout << "I`m in forward" << endl;
   // cout << "forwardInv:" << endl << b[0][0] << " " << b[0][1] << endl << b[1][0] << " " << b[1][1] << endl << "__" << endl;
   // cout << "forwardA:" << endl << a[0][0] << " " << a[0][1] << endl << a[1][0] << " " << a[1][1] << endl << "__" << endl;
}


void gauseback(double** b, double** a, int n, int k)
{
    int j, i;
    double temp= a[k][k];
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
   // cout << "backInv:" << endl << b[0][0] << " " << b[0][1] << endl << b[1][0] << " " << b[1][1] << endl << "__" << endl;
   // cout << "backA:" << endl << a[0][0] << " " << a[0][1] << endl << a[1][0] << " " << a[1][1] << endl << "__" << endl;
}

void inverse(double** reala, double** b, int n)
{
    double** a = new double* [n];

    for (int i = 0; i < n; ++i)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; ++j)
            a[i][j] = reala[i][j];
    }
   // cout << "Ain:" << endl << a[0][0] << " " << a[0][1] << endl << a[1][0] << " " << a[1][1] << endl << "__" << endl;
    for (int i = 0; i < n; ++i) 
    {
        gauseforward(b, a, n, i);
       // cout << "After:" << endl << b[0][0] << " " << b[0][1] << endl << b[1][0] << " " << b[1][1] << endl << "__" << endl;
    }
    
    for (int i = n - 1; i >= 0; --i)
        gauseback(b, a, n, i);

}


class Newton
{
    double eps = 0.1;
    double* prevX = nullptr;
    double** invMatr = nullptr;
    double* p = nullptr;
    double* temp = nullptr;
   
public:
    double getEps() { return eps; }
    void matByRow(double** mat, double* vec, double* p, int n)
    {
        double sum = 0;
        for (int i = 0; i < n; ++i)
        {
            sum = 0;
            for (int j = 0; j < n; ++j)
            {
                sum += mat[i][j] * vec[j];
            }
            p[i] = -sum;
        }
    }
    double* calcP(Derivaties *d)
    {
        int n = d->getN();
        p = new double[n];
        invMatr = new double* [n];
        for (int i = 0; i < n; ++i) 
        {
            invMatr[i] = new double[n] {0};
            invMatr[i][i] = 1;
        }

        //cout << "hes:" << endl << d->getHessian()[0][0] << d->getHessian()[0][1] << endl << d->getHessian()[1][0] << " " << d->getHessian()[1][1]<<endl<<"__"<<endl;
        
        inverse(d->getHessian(), invMatr, n);
        //cout << "Invhes:" << endl << invMatr[0][0] << invMatr[0][1] << endl << invMatr[1][0] << " " << invMatr[1][1] << endl << "__" << endl;
        //cout << "hes:" << endl << d->getHessian()[0][0] << d->getHessian()[0][1] << endl << d->getHessian()[1][0] << " " << d->getHessian()[1][1] << endl << "__" << endl;

        matByRow(invMatr, d->getGradient(), p, n);
        
        for (int i = 0; i < n; ++i)
        {
            delete[] invMatr[i];
        }        
       // cout <<"p="<< p[0] << " " << p[1]<<endl;
        return p;
    }

    double getNorma(double* x, int n)
    {
        double norm = 0;
        for (int i = 0; i < n; ++i)
        {
            norm += x[i] * x[i];
        }
        norm = sqrt(norm);
        return norm;
    }

    double getNorma(double x)
    {
        return abs(x);
    }

    bool Stop(double* x, Function& f, Derivaties *d,int ind)
    {
        if (getNorma(d->getGradient(), d->getN()) < eps)
            return false;
        if (ind>0)
        {
            temp = new double[f.getK()]{0};
  
            for(int i = 0; i < f.getK();++i)
            {
                temp[i] = x[i] - prevX[i];
                cout << "temp[" << i << "]=" << temp[i] << endl;                
            }
            cout << endl;
            if (getNorma(temp, f.getK()) < eps)
            {
                delete temp;
                return false;
            }

            delete temp;

            if (getNorma((f.getf(x) - f.getf(prevX)) / f.getf(x)) < eps)
            {
                return false;
            }
        }

  
        

        return true;
    }

    void Nyton(double* x, Function& f)
    {
        double eps = 0.1;
        int n = f.getK();
        Derivaties* d =new Derivaties(n, eps);
        
        d->calcGradient(f, x);
        d->calcHessian(f, x);

        double* tempP= new double[n];
      
        prevX = new double[n] {0};
        double alpha = 1;
        for (int i = 0; i > 500 || Stop(x, f, d, i); ++i,  alpha/=2  )
        {

            tempP = calcP(d);
            for (int j = 0; j < n; ++j)
            {
                prevX[j] = x[j];
                x[j] = x[j] + tempP[j]*alpha;
                cout << "x[" << j << "]= " << x[j] << endl;
                cout << "prev[" << j << "]= " << prevX[j] << endl;
            }
            cout << endl;
            d->calcGradient(f, x);
            d->calcHessian(f, x);
            
        }

        for (int j = 0; j < n; ++j)
        {
            prevX[j] = x[j];
        }
        delete invMatr;


        //cout <<"prez: "<< prevX[0] << " " << prevX[1]<<endl;
        // prevX = x;
        // cout <<"xrez:" <<prevX[0]<<" "<<prevX[1]<< endl;

    }

    double* getRez()
    {
        return prevX;
    }
   
};



int main()
{
    Function* f;
    f= new function2();
    Newton rez; 
    double* x = new double[2]{100, 100};
    rez.Nyton(x, *f);
    cout << "\nrez:" << rez.getRez()[0] << " " << rez.getRez()[1];
    

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку" 

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
