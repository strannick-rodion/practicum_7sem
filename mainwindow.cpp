#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mousePos(QMouseEvent*)));
    connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mouseClick(QMouseEvent*)));
    Plot(ui->plot);
    x0 = -10^5;
    y0 = -10^5;
    methodNum=2;
    functionNum=3;
}

MainWindow::~MainWindow()
{
    delete ui;
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
                    z=(x*x+y-11)*(x*x+y-11)+(y*y+x-7)*(y*y+x-7);

                    break;
                  case 2:
                    z=(y - 3) * (y - 3) + (x + 5) * (x + 5) - 3;
                    break;
                  case 3:
              z=(x+2*y-7)*(x+2*y-7)+(2*x+y-5)*(2*x+y-5);
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

void MainWindow::on_tabWidget_2_tabBarClicked(int index)
{
    ui->ready->setText("Click on the graph to select \na starting point");
    if (index == 0)
        {
            functionNum = 1;
        }
        else if(index == 1)
        {
            functionNum = 2;
        }
        else
        {
            functionNum = 3;
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
                   case 3:
           {
               f = new function2();
               break;
            }}

           Plot(ui->plot);
           ui->plot->replot();
   }


void MainWindow::mousePos(QMouseEvent* event)
{

}

void MainWindow::mouseClick(QMouseEvent* event)
{


    ui->plot->mouseMove(event);
    geomX = ui->plot->xAxis->pixelToCoord(event->x());
    geomY = ui->plot->yAxis->pixelToCoord(event->y());


    ui->ready->setText("x=" +  QString::number(geomX) + "\ny= " + QString::number(geomY) + "\n");

    x = {geomX, geomY};




 QString textArea;
textArea= ui->areaf->currentText();


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
    case 3:
    {
        f = new function3();



        break;
    }
     }



    if(textArea == "(-5,-5)x(5,5)")
    {
        a = { -5, -5 };
        b = { 5, 5 };
        areaOpt.setArea(a, b);
        areaNum = 2;
    }
    else
    {
    if(textArea == "(0,10)x(0,10)")
    {
        a = { 0, 0 };
        b = { 10, 10 };
        areaOpt.setArea(a, b);

    }
    else{
    if(textArea == "(-10,15)x(-20,20)")
    {

               a = { -10, -20 };
               b = { 15, 20 };
               areaOpt.setArea(a, b);

    }
     else{ if(textArea == "(-4,-4)x(4,4)"){
        a = { -4, -4 };
        b = { 4, 4 };
        areaOpt.setArea(a, b);
        }
        else{
       if( textArea== "(-15,15)x(-7,13)")
       {
           a = { -15, -7 };
           b = { 15, 13 };
           areaOpt.setArea(a, b);
           areaNum = 1;
       }
       else{
       if( textArea== "(-20,10)x(-10,20)")
       {
           a = { -20, -10 };
           b = { 10, 20 };
           areaOpt.setArea(a, b);

       }}}}}}
     switch (methodNum) {
        case 1:
          {
         QString textStop = ui->stopChoice->currentText();
         if( textStop== "Gradient")
         {
             stopCrit = 1;
         }
         else if(textStop == "Function arguments")
         {
             stopCrit = 2;
         }
         else if(textStop == "Function value")
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



            }

            QCPCurve *trajectory = new QCPCurve(ui->plot->xAxis, ui->plot->yAxis);
            trajectory->setData(plotX, plotY);
            trajectory->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 0), QBrush(Qt::white), 4));
            trajectory->setPen(QPen(Qt::white, 1));

            ui->plot->replot();

            ui->rezZn->setText("Результат: \nNumber of iteration:" +QString::number(rez->getIter())+"\nx="+QString::number(rez->getRez()[0])+", y="+QString::number(rez->getRez()[1]) +"\nf(x,y)=" +QString::number(f->getf(rez->getRez())));



}
