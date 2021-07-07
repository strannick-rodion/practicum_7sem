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
    double geomX,geomY;
    Optimisation * rez;
    int methodNum;
    double eps, x0, y0,x1,y1;
    int areaNum=1, ind;
    int stopCrit=1;
    vector<double> a = { 0 }, b = { 0 }, x = { 0 };
    Area areaOpt;
    void Plot(QCustomPlot * customPlot);
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_tabWidget_2_tabBarClicked(int index);
    void mousePos(QMouseEvent* event);

       void mouseClick(QMouseEvent* event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
