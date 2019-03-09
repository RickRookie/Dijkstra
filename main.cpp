#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
//本不是放在这个
// float x1=x[i];
//float y1 = y[i];
//       float l = 10.0;                   //箭头的那长度
//       float a = 0.5;                       //箭头与线段角度
//       float x2 = x[j];
//       float y2 = y[j];
//       float x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - x1)) - a);
//       float y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - x1)) - a);
//       float x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - y1)) - a);
//       float y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - y1)) - a);
