#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "wdigraph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void drawArrow(QPoint startPoint, QPoint endPoint, QPainter &p);
    void drawArrowColor(QPoint startPoint, QPoint endPoint, QPainter &p);
    int FindDDMinIndex(int *d);
    template <class T>
    void getWeight(AdjacencyWDigraph<T> *awg);//把边的信息放入数组
    int Flag[MAX_SIZE][MAX_SIZE];
private slots:
    void on_pushButton_clicked();

    void on_pushButton_draw_clicked();

    void on_pushButton_next_clicked();

private:
    Ui::MainWindow *ui;
    AdjacencyWDigraph<int> *awg;
    int NN; //结点数
    int WW[MAX_SIZE][MAX_SIZE]; //权值
    int RR[MAX_SIZE][MAX_SIZE]; //随机边
    int DD[MAX_SIZE]; //d中返回最短距离
    int Dd[MAX_SIZE]; //复制DD数组
    int PP[MAX_SIZE]; //p中返回前继顶点
    int SP[MAX_SIZE]; //sp中为结点序号
    int SS; //源点
    int order; //DD中目前最小的索引
    int I; //表示点击next的次数


};

#endif // MAINWINDOW_H
