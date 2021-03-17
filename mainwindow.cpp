#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Plot(ui->plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
     QString textFunction = ui->functionChoice->currentText();
     if(textFunction == "f1")
         {
             functionNum = 1;
         }
         else if(textFunction == "f2")
         {
             functionNum = 2;
         }
     QString textMethod = ui->methodChoice->currentText();
         if(textMethod == "metod1")
         {
             methodNum = 1;
         }
         else if(textMethod == "metod2")
         {
             methodNum = 2;
         }

         QString textArea = ui->areaChoice->currentText();
         if( textArea== "area1")
         {
             areaNum = 1;
         }
         else if(textMethod == "area2")
         {
             methodNum = 2;
         }

         QString textStop = ui->stopChoice->currentText();
         if( textArea== "stop1")
         {
             stopCrit = 1;
         }
         else if(textMethod == "stop2")
         {
             stopCrit = 2;
         }
         x={5,5};
         eps = ui->epsZn->text().toDouble();

         switch (functionNum)
         {
                     case 1:
                     {
                         f = new function1();
                         break;

                     }
                     case 2:
                     {
                         f = new function2();
                         break;
                     }
          }


         switch (areaNum)
         {
                case 1:
                     {
                        a = { -50, -50 };
                        b = { 50, 50 };
                        areaOpt.setArea(a, b);

                         break;

                     }
                case 2:
                    {
                        a = { -10, -20 };
                        b = { 10, 20 };
                        areaOpt.setArea(a, b);

                    }
         }


          switch (methodNum) {
             case 1:
                     {
                          rez = new Newton();
                          rez->calcOptim(x, *f, areaOpt, stopCrit, eps);
                         break;
                     }
             case 2:
                     {
                          rez = new RandomSearch();
                          rez->calcOptim(x, *f, areaOpt, stopCrit, eps);
                         break;
                     }
                 }
          ui->rezZn->setText("Результат: \nNumber of iteration:" +QString::number(rez->getIter())+"\nx="+QString::number(rez->getRez()[0])+", y="+QString::number(rez->getRez()[1]) +"\nf(x,y)=" +QString::number(f->getf(rez->getRez())));
          Plot(ui->plot);
                 ui->plot->replot();

                 QVector<double> plotX = QVector<double>(rez->getVecX().size(), 0);
                 QVector<double> plotY = QVector<double>(rez->getVecX().size(), 0);

                 for (int i=0;i<(rez->getVecX().size()) ;++i )
                 {
                     plotX[i]=rez->getVecX()[i][0];
                     plotY[i]=rez->getVecX()[i][1];
                 }

                 QCPCurve *trajectory = new QCPCurve(ui->plot->xAxis, ui->plot->yAxis);
                 trajectory->setData(plotX, plotX);
                 trajectory->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 0), QBrush(Qt::black), 4));
                 trajectory->setPen(QPen(Qt::black, 1));

                 ui->plot->replot();
}

void MainWindow::Plot(QCustomPlot * customPlot){
      customPlot->clearPlottables();
      customPlot->axisRect()->setupFullAxesBox(true);
      customPlot->xAxis->setLabel("x");
      customPlot->yAxis->setLabel("y");

      QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
      int numOfx = 100;
      int numOfy = 100;


      colorMap->data()->setSize(numOfx, numOfy);
      colorMap->data()->setRange(QCPRange(areaOpt.getFirst()[0], areaOpt.getSecond()[0]), QCPRange(areaOpt.getFirst()[1], areaOpt.getSecond()[0]));
      double x, y, z;

      for (int x_i = 0; x_i < numOfx; ++x_i)
      {
        for (int y_i = 0; y_i < numOfy; ++y_i)
        {
          colorMap->data()->cellToCoord(x_i, y_i, &x, &y);
          switch (functionNum){
                  case 1:
                    z=(y+8)*(y+8)+(x-10)*(x-10) +20;

                    break;
                  case 2:
                    z=(y - 3) * (y - 3) + (x + 5) * (x + 5) - 3;
                    break;
          }
          colorMap->data()->setCell(x_i, y_i, z);
        }
      }


      QCPColorScale *colorScale = new QCPColorScale(customPlot);
      customPlot->plotLayout()->addElement(0, 1, colorScale);
      colorScale->setType(QCPAxis::atRight);
      colorMap->setColorScale(colorScale);

      colorMap->setGradient(QCPColorGradient::gpCandy);

      colorMap->rescaleDataRange();


      QCPMarginGroup *group = new QCPMarginGroup(customPlot);
      colorScale->setMarginGroup(QCP::msTop|QCP::msBottom, group);
      customPlot->axisRect()->setMarginGroup(QCP::msTop|QCP::msBottom, group);


      customPlot->rescaleAxes();
      customPlot->replot();

}
