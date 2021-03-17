#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Plot(ui->plot);
    x0 = -10^5;
    y0 = -10^5;
    methodNum=1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
     QString textFunction = ui->functionChoice->currentText();
     if(textFunction == "f(x,y)=(y+8)^2+(x-10)^2+20")
         {
             functionNum = 1;
         }
         else if(textFunction == "f(x,y)=(y-3)^2+(x + 5)^2-3")
         {
             functionNum = 2;
         }


         QString textArea = ui->areaChoice->currentText();
         if( textArea== "(-20,50)x(-50,30)")
         {
             areaNum = 1;
         }
         else if(textArea == "(-10,15)x(-20,20)")
         {
             areaNum = 2;
         }



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
                        a = { -20, -50 };
                        b = { 50, 30 };
                        areaOpt.setArea(a, b);

                         break;

                     }
                case 2:
                    {
                        a = { -10, -20 };
                        b = { 15, 20 };
                        areaOpt.setArea(a, b);
                         break;

                    }
         }
            x1 = ui->xZn->text().toDouble();
            y1 = ui->yZn->text().toDouble();
            x={x1,y1};
          switch (methodNum) {
             case 1:
               {
              QString textStop = ui->stopChoice->currentText();
              if( textStop== "stop1")
              {
                  stopCrit = 1;
              }
              else if(textStop == "stop2")
              {
                  stopCrit = 2;
              }
              else if(textStop == "stop3")
              {
                  stopCrit = 3;
              }

              eps = ui->epsZn->text().toDouble();
              ind=ui->indNewton->text().toInt();
                          rez = new Newton();
                          rez->calcOptim(x, *f, areaOpt, stopCrit, eps,ind);
                         break;
                     }
             case 2:
                     {
                            eps = ui->epsRand->text().toDouble();
                            ind=ui->indRand->text().toInt();
                          rez = new RandomSearch();
                          rez->calcOptim(x, *f, areaOpt, stopCrit, eps,ind);
                         break;
                     }
                 }

          Plot(ui->plot);
                 ui->plot->replot();
                int n=rez->getSize();
                cout<<n<<endl;
                 QVector<double> plotX = QVector<double>(n, 0);
                 QVector<double> plotY = QVector<double>(n, 0);

                 for (int i=0;i<n ;++i )
                 {

                         plotX[i]=rez->getVecX(i,0);
                         plotY[i]=rez->getVecX(i,1);
                         cout<<"out:"<<plotX[i]<<" "<<plotY[i]<<endl;


                 }

                 QCPCurve *trajectory = new QCPCurve(ui->plot->xAxis, ui->plot->yAxis);
                 trajectory->setData(plotX, plotX);
                 trajectory->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 0), QBrush(Qt::white), 4));
                 trajectory->setPen(QPen(Qt::white, 1));

                 ui->plot->replot();

                 ui->rezZn->setText("Результат: \nNumber of iteration:" +QString::number(rez->getIter())+"\nx="+QString::number(rez->getRez()[0])+", y="+QString::number(rez->getRez()[1]) +"\nf(x,y)=" +QString::number(f->getf(rez->getRez())));

}

void MainWindow::Plot(QCustomPlot * customPlot){
      customPlot->clearPlottables();
      customPlot->axisRect()->setupFullAxesBox(true);
      customPlot->xAxis->setLabel("x");
      customPlot->yAxis->setLabel("y");

      QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
      int numOfx = 200;
      int numOfy = 200;


      colorMap->data()->setSize(numOfx, numOfy);
      colorMap->data()->setRange(QCPRange(areaOpt.getFirst()[0], areaOpt.getSecond()[0]), QCPRange(areaOpt.getFirst()[1], areaOpt.getSecond()[1]));
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

      colorMap->setGradient(QCPColorGradient::gpThermal);

      colorMap->rescaleDataRange();


      QCPMarginGroup *group = new QCPMarginGroup(customPlot);
      colorScale->setMarginGroup(QCP::msTop|QCP::msBottom, group);
      customPlot->axisRect()->setMarginGroup(QCP::msTop|QCP::msBottom, group);


      customPlot->rescaleAxes();
      customPlot->replot();

}



void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index == 0)
        {
            methodNum = 1;
        }
        else
        {
            methodNum = 2;
        }
}
