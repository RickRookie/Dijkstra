#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QtMath>
#include <QDebug>
void MainWindow::drawArrow(QPoint startPoint, QPoint endPoint, QPainter &p)
{
    double par = 15.0;//箭头部分三角形的腰长
    double slopy = atan2((endPoint.y() - startPoint.y()), (endPoint.x() - startPoint.x()));
    double cosy = cos(slopy);
    double siny = sin(slopy);
    QPoint point1 = QPoint(endPoint.x() + int(-par*cosy - (par / 2.0*siny)), endPoint.y() + int(-par*siny + (par / 2.0*cosy)));
    QPoint point2 = QPoint(endPoint.x() + int(-par*cosy + (par / 2.0*siny)), endPoint.y() - int(par / 2.0*cosy + par*siny));
    QPoint points[3] = { endPoint, point1, point2 };
    p.setRenderHint(QPainter::Antialiasing, true);//消锯齿
    QPen drawTrianglePen;//创建画笔
    //drawTrianglePen.setColor(Qt::red); //红色
    drawTrianglePen.setWidth(1);
    //drawTrianglePen.setStyle(Qt::DashLine); //虚线
    p.setPen(drawTrianglePen);
    p.drawPolygon(points, 3);//绘制箭头部分
    int offsetX = int(par*siny / 3);
    int offsetY = int(par*cosy / 3);
    QPoint point3, point4;
    point3 = QPoint(endPoint.x() + int(-par*cosy - (par / 2.0*siny)) + offsetX, endPoint.y() + int(-par*siny + (par / 5.0*cosy)) - offsetY);
    point4 = QPoint(endPoint.x() + int(-par*cosy + (par / 2.0*siny) - offsetX), endPoint.y() - int(par / 5.0*cosy + par*siny) + offsetY);
    QPoint arrowBodyPoints[3] = { startPoint, point3, point4 };
    p.drawPolygon(arrowBodyPoints, 3);//绘制箭身部分
}
void MainWindow::drawArrowColor(QPoint startPoint, QPoint endPoint, QPainter &p)
{
    double par = 15.0;//箭头部分三角形的腰长
    double slopy = atan2((endPoint.y() - startPoint.y()), (endPoint.x() - startPoint.x()));
    double cosy = cos(slopy);
    double siny = sin(slopy);
    QPoint point1 = QPoint(endPoint.x() + int(-par*cosy - (par / 2.0*siny)), endPoint.y() + int(-par*siny + (par / 2.0*cosy)));
    QPoint point2 = QPoint(endPoint.x() + int(-par*cosy + (par / 2.0*siny)), endPoint.y() - int(par / 2.0*cosy + par*siny));
    QPoint points[3] = { endPoint, point1, point2 };
    p.setRenderHint(QPainter::Antialiasing, true);//消锯齿
    QPen drawTrianglePen;//创建画笔
    drawTrianglePen.setColor(Qt::red); //红色
    drawTrianglePen.setWidth(1);
    p.setPen(drawTrianglePen);
    p.drawPolygon(points, 3);//绘制箭头部分
    int offsetX = int(par*siny / 3);
    int offsetY = int(par*cosy / 3);
    QPoint point3, point4;
    point3 = QPoint(endPoint.x() + int(-par*cosy - (par / 2.0*siny)) + offsetX, endPoint.y() + int(-par*siny + (par / 5.0*cosy)) - offsetY);
    point4 = QPoint(endPoint.x() + int(-par*cosy + (par / 2.0*siny) - offsetX), endPoint.y() - int(par / 5.0*cosy + par*siny) + offsetY);
    QPoint arrowBodyPoints[3] = { startPoint, point3, point4 };
    p.drawPolygon(arrowBodyPoints, 3);//绘制箭身部分
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    NN = 1; //默认的结点数
    SS = 1; //默认的源点
    I = 0;  //默认的NEXT点击次数
    awg = new AdjacencyWDigraph<int>(NN,0);
    for(int i=0;i<MAX_SIZE;i++)
    {
        for (int j=0;j<MAX_SIZE;j++)
        {
            WW[i][j] = 0;
        }
    }
    for (int i = 0; i < MAX_SIZE; i++) {  //初始化
        DD[i] = 0;
    }
    for (int i = 0; i <MAX_SIZE; i++) {
        SP[i] = i;
    }

}

template <class T>
void MainWindow::getWeight(AdjacencyWDigraph<T>* awg)
{
    int w;
    int r;
    for(int i=1;i<=NN;i++)
    {
        for(int j=i+1;j<=NN;j++)
        {
            w = rand()%10+1; // 1-10
            r = rand()%3; //0 - 2
            if (r==0) {
                w=r;
            }
            if(r>0)  awg->Add(i,j,w); //把边的信息加入到矩阵中
            RR[i][j] = r; //用来判断有没有边
            WW[i][j] = w;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    NN = ui->lineEdit->text().toInt();
    awg = new AdjacencyWDigraph<int>(NN,0);
    getWeight(awg); //获取全部边的信息
    for(int i=0;i<MAX_SIZE;i++)
    {
        for (int j=0;j<MAX_SIZE;j++)
        {
            Flag[i][j] = 0;
        }
    }
    this->repaint();
    //this->update();
}
  void MainWindow::paintEvent(QPaintEvent *)
  {
      QPainter p(this);
      // QPainter painter1(this);
       QString png0 = ":/img/";
       QString png3 = ".png";
       int x[] = {0,97,200,380,475,502,367,222,94,55};
       int y[] = {0,160,100,200,360,460,582,605,515,369};

       for (int i=1;i<=NN;i++)
       {
           QString png1 = QString::number(i);
           QString png = png0+png1+png3;
           QPixmap pix = QPixmap(png);
          p.drawPixmap(x[i],y[i],30,30,pix);

       }
       for (int i=1;i<=NN;i++)
       {
          for(int j=i+1;j<=NN;j++)
          {
              if(RR[i][j]==0) //判断从i到j有没有边
              {
                  continue; //跳过
              } else {

               QPoint start = QPoint(x[i],y[i]);
               QPoint end = QPoint(x[j],y[j]);
               QPoint mid = QPoint((x[i]+x[j])/2,(y[i]+y[j])/2);

               QString weight = QString::number(WW[i][j]);
               QFont qf = QFont();
               QPen qp;
               qp.setColor(Qt::black);
               qf.setPixelSize(25);
               p.setPen(qp);
               p.setFont(qf);
               p.drawText(mid,weight);
               //qDebug()<<"Flag: "<<Flag[i][j];
               if(Flag[i][j]==1)

               { this->drawArrowColor(start,end,p);
               } else {
               this->drawArrow(start,end,p);
               }

              }
          }
       }
  }
  void findPaths(int p[],int s, int i)
  {
      Chain<int> L; //用来存路径
      int m = 0;
      int n = 0;
      m = p[i];
      while (m)
      {
          L = L.Insert(0, m);
          n++;
          m = p[m];
      }
      L = L.Insert(0, s); //加入起点
      L = L.Insert(n+1, i); //加入终点
      int x = 0;
      n = n + 2; //总的结点数
      while (n)
      {
          L= L.Delete(1,x);
          cout << x;
          if (n>1) cout<< "->";
          n--;
      }
  }
  template<class T>
  void _Bubble(T a[], T b[],int n)
  {
      //把数组中最大的元素通过冒泡移到右边
      for (int i = 1; i < n ; i++) {
          if (a[i] > a[i + 1]) {
              Swap(a[i], a[i + 1]);
              Swap(b[i], b[i + 1]);
          }
      }
  }
  template<class T>
  void _BubbleSort(T a[], T b[],  int n)
  { //对数组中的 n个元素进行冒泡排序
      for (int i = n; i> 1; i--) {
          _Bubble(a,b, i);
      }
  }
  template <class T>
  void Swap(T& a, T& b)
  {
      //交换啊a,b .
      T temp = a;
      a = b;
      b = temp;
  }
void MainWindow::on_pushButton_draw_clicked()
{
     NN = ui->lineEdit->text().toInt();
     //awg = new AdjacencyWDigraph<int>(NN,0);
     awg->ShortestPaths(SS,DD,PP);
     for(int i=1;i<=NN;i++) Dd[i] = DD[i];

     //_BubbleSort(DD,SP,NN);
     QMessageBox::about(this,"ok","成功!");
     //this->repaint();

}
int MainWindow::FindDDMinIndex(int *d)
{
    int m =1;
    for(int i=1;i<=NN;i++)
    {
        if(d[i]<d[m]) m = i;
    }
    d[m] = 1000;
    return m;
}

void MainWindow::on_pushButton_next_clicked()
{
    SS = ui->lineEdit_first->text().toInt();
   for(int i=1;i<=NN;i++) qDebug()<<Dd[i];
//    for(int i=1;i<=NN;i++) qDebug()<<DD[i];
//    for(int i=1;i<=NN;i++) qDebug()<<PP[i];
    //for(int i=1;i<=NN;i++) qDebug()<<DD[i];
    order = this->FindDDMinIndex(Dd);
    qDebug()<<order;
    int j = PP[order];
    if(j==0) {
        //Flag[SS][order]=1;
        //qDebug()<<Flag[SS][order];
         qDebug()<<"index: ";
    } else {
    Flag[j][order] = 1;
    //qDebug()<<Flag[j][order];
    qDebug()<<"index: ";
    }
    I++;
    if(I==NN) QMessageBox::about(this,"OVER","演示完毕!");
    this->repaint();

}
