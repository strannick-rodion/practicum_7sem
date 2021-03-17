#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "real/Area.h"
#include "real/function.h"
#include "real/optimisation.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Function* f;
    int functionNum;
    Optimisation * rez;
    int methodNum;
    double eps;
    int areaNum;
    int stopCrit;
    vector<double> a = { 0 }, b = { 0 }, x = { 0 };
    Area areaOpt;
    void Plot(QCustomPlot * customPlot);
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
