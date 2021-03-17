#include"Derivaties.h"


vector<vector<double>> Derivaties::getHessian()
{
    return hessian;
}
vector<double> Derivaties::getGradient()
{
    return gradient;
}

int Derivaties::getN()
{
    return n;
}
void Derivaties::calcGradient(Function& f, vector<double>& x)
{
    double rtemp, ltemp;
    if (!gradient.empty())
    {
        gradient.clear();
    }
    for (int i = 0; i < n; ++i)
    {
        x[i] -= eps;
        ltemp = f.getf(x);
        x[i] += 2 * eps;
        rtemp = f.getf(x);
        gradient.push_back((rtemp - ltemp) / (2 * eps));
        x[i] -= eps;

    }
}
void Derivaties::calcHessian(Function& f, vector<double>x)
{
    double ftemp1, ftemp2, ftemp3;
    if (!hessian.empty())
    {
        hessian.clear();
    }
    vector<double> vectemp(n, 0);
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
            vectemp[j] = (ftemp3 - ftemp2 - ftemp1 + f.getf(x)) / (eps * eps);
        }
        hessian.push_back(vectemp);
    }
    cout << "hessian:" << endl << hessian[0][0] << " " << hessian[0][1] << endl << hessian[1][0] << " " << hessian[1][1] << endl << "__" << endl;

}

void gauseforward(vector<vector<double>>& b, vector<vector<double>>& a, int n, int k)
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
    // cout << "backInv:" << endl << b[0][0] << " " << b[0][1] << endl << b[1][0] << " " << b[1][1] << endl << "__" << endl;
    // cout << "backA:" << endl << a[0][0] << " " << a[0][1] << endl << a[1][0] << " " << a[1][1] << endl << "__" << endl;
}

void inverse(const vector<vector<double>>& a, vector<vector<double>>& b, int n)
{
    vector<vector<double>> temp(a);
    // cout << "Ain:" << endl << a[0][0] << " " << a[0][1] << endl << a[1][0] << " " << a[1][1] << endl << "__" << endl;
    for (int i = 0; i < n; ++i)
    {
        gauseforward(b, temp, n, i);
        cout << "After:" << endl << b[0][0] << " " << b[0][1] << endl << b[1][0] << " " << b[1][1] << endl << "__" << endl;
    }

    for (int i = n - 1; i >= 0; --i)
        gauseback(b, temp, n, i);

}