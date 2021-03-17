 // NytonBacktracking.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <vector>
#include "optimisation.h"
#include"Area.h"
#include"function.h"

using namespace std;


int main()
{

    vector<double> a = { 0 }, b = { 0 }, x = { 0 };
    Function* f=nullptr;
    int funcNum;
    Optimisation* rez;
    int areaNum, maxIter;
    Area areaOpt(a, b);
    double eps;

    cout << "Choose function:" << endl;
    cout << "1. f(x, y) = (y +8)^2 + (x -10)^2 +20"<<endl;
    cout << "2. f(x, y) = (y - 3)^2 + (x + 5)^2 - 3" << endl;
    cout << "3. f(x, y, z) = x^2 + y^2 + z^2 + 5" << endl;
    cout << "Enter function number:" << endl;
    std::cin >> funcNum;

    switch (funcNum)
    {
     case 1:
    {
        f = new function1();
        cout << "Choose area:" << endl;
        cout << "1.(-50, 50)x(-50, 50)" << endl;
        cout << "2.(-10, 10)x(-20, 20)" << endl;
        cout << "Enter area number:" << endl;
        cin >> areaNum;
        switch (areaNum)
        {
        case 1:

            a = { -50, -50 };
            b = { 50, 50 };
            areaOpt.setArea(a, b);
            x = { 40, 40 };
            break;

        default:

            a = { -10, -20 };
            b = { 10, 20 };
            areaOpt.setArea(a, b);
            x = { 5, 5 };
            break;

           

        }
        break;
    }
    case 2:
    {
        f = new function2();
        
        cout << "Choose area:" << endl;
        cout << "1.(-50, 50)x(-50, 50)" << endl;
        cout << "2.(-10, 10)x(-20, 20)" << endl;
        cout << "Enter area number:" << endl;
        cin >> areaNum;
        switch (areaNum)
        {
        case 1:

            a = { -50, -50 };
            b = { 50, 50 };
            areaOpt.setArea(a, b);
            x = { 41, 40 };
            break;

        default:

            a = { -10, -20 };
            b = { 10, 20 };
            areaOpt.setArea(a, b);
            x = { 5, 5 };
            break;

            
        }
        break;
    }
    default:
    {
        f = new function3();
        
        cout << "Choose area:" << endl;
        cout << "1.(-50, 50)x(-50, 50))x(-50, 50)" << endl;
        cout << "2.(-10, 10)x(-20, 20))x(-15, 30)" << endl;
        cout << "Enter area number:" << endl;
        cin >> areaNum;
        switch (areaNum)
        {
        case 1:

            a = { -50, -50 ,-50 };
            b = { 50, 50,50 };
            areaOpt.setArea(a, b);
            x = { 20, 15 ,-10 };
            break;

        default:

            a = { -10, -20,-15 };
            b = { 10, 20 ,30 };
            areaOpt.setArea(a, b);
            x = { 5, 5,7 };
            break;

            
        }
        break;
    }
    }
   
   
    cout << "Choose optimization method" << endl;
    cout << "1. Newton backtraking" << endl;
    cout << "2. Random search" << endl;
    int methodNum;
    cout << "Enter method number:" << endl;
    cin >> methodNum;
    int stopCrit;
    
    switch (methodNum)
    {
    case 1:
    {
       
        cout << "Choose stopping criterion" << endl;
        cout << "1. Gradient" << endl;
        cout << "2. Function arguments" << endl;
        cout << "3. Function value" << endl;
        cout << "Enter stopping criterion number:" << endl;
        cin >> stopCrit;
        cout << "Enter eps in (0,1):" << endl;
        cin >> eps;
        cout << "Enter maximal number of iteration:" << endl;
        cin >> maxIter;
        rez = new Newton();
        rez->calcOptim(x, *f, areaOpt, stopCrit, eps,maxIter);
        break;
    }
    default:
    {
        cout << "Choose stopping criterion" << endl;
        cout << "1. Last change>10" << endl;
        cout << "Enter eps in (0,1):" << endl;
        cin >> eps;
        cin >> stopCrit;
        cout << "Enter maximal number of iteration:" << endl;
        cin >> maxIter;
        rez = new RandomSearch();
        rez->calcOptim(x, *f, areaOpt, stopCrit, eps, maxIter);
        break;
    }
    }


    cout <<endl <<"________Results__________"<<endl;
    cout << "Number of iteration: " << rez->getIter() << endl;
    

    for (int i = 0; i < f->getK(); ++i)
    {
        cout <<"x["<<i<<"]="<< rez->getRez()[i] << ", ";
    }
    cout << endl;

    cout << "f= " <<f->getf(rez->getRez()) << endl;
    cout << rez->getSize() << endl;
   int n = rez->getSize();
    for (int i = 0; i <n; ++i)
    {
        for (int j = 0; j < f->getK(); ++j)
        {
            cout << i<< ":" << rez->getVecX(i,j) << " " ;
        }
        cout << endl;
    }
    
 
    

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
