#ifndef WDIGRAPH_H
#define WDIGRAPH_H
#define MAX_SIZE 11
#endif // WDIGRAPH_H
#include <iostream>
#include <ctime>
using namespace std;
void findPaths(int p[],int s, int i);
template<class T>
void _Bubble(T a[], T b[],  int n);

template<class T>
void _BubbleSort(T a[], T b[],  int n);

template <class T>
void Swap(T& a, T& b);
template <class T>
void Make2DArray(T **& x, int rows, int cols)
{ //创建一个二维数组，  记得手动释放空间
  // 创建行指针
    x = new T *[rows];
    //为每一行分配空间
    for (int i = 0; i < rows; i++) {
        x[i] = new T[cols];
    }
}
template <class T>
void Delete2DArray(T **&x, int rows)
{ //删除二维数组
  // 释放为每一行所分配的空间
    for (int i = 0; i < rows; i++) {
        delete[] x[i];
    }
    //删除行指针
    delete[] x;
    x = NULL;
}
class OutOfBounds :exception {
public:
    OutOfBounds() {
        cout << "out of bounds" << endl;
    }
};
class BadInput :exception {
public:
    BadInput() {
        cout << "bad input" << endl;
    }
};
template <class T>
class Node {
    template <class T> friend class LinkedQueue;
    template <class T> friend class Chain;
    template <class T> friend class ChainIterator;
private:
    T data;
    Node<T> *link;

};
template <class T>
class Chain {
public:
    Chain() { first = 0; }
    bool IsEmpty() const { return first == 0; }
    Chain<T>& Delete(int k, T& x);
    Chain<T>& Insert(int k, const T& x);
    Chain<T>& Delete(T &x); //删除值为x的节点
    int Length() const;
    int Search(const T&x) const;
    template <class T> friend class ChainIterator;
private:
    Node<T> *first;
};
template<class T>
class ChainIterator {
public:
    T * Initialize(const Chain<T>& c) {
        location = c.first;
        if (location) return &location->data; //数据
        return 0;
    }
    T* Next() {
        if (!location) return 0;
        location = location->link;
        if (location) return &location->data;
        return 0;
    }
private:
    Node<T>* location;
};
template <class T>
class LinkedQueue {
    // FIFO对象
public:
    LinkedQueue() { front = rear = 0; }
    bool IsEmpty() const { return ((front) ? false : true); }
    LinkedQueue<T>& Add(const T& x);
    LinkedQueue<T>& Delete(T& x);
private:
    Node<T>* front; //指向第一个节点
    Node<T>* rear; //指向最后一个节点
};

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T & x)
{ //把x添加到队列的尾部
  // 为新元素创建链表节点
    Node<T>* p = new Node<T>;
    p->data = x;
    p->link = 0;
    // 在队列尾部添加新节点
    if (front) rear->link = p; // 队列不为空
    else front = p; // 队列为空
    rear = p;
    // TODO: 在此处插入 return 语句
    return *this;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Delete(T & x)
{ // 删除第一个元素，并将其放入x
  //  如果队列为空，则引发异常

  // 保存第一个节点中的元素
    x = front->data;
    // 删除第一个节点
    Node<T> *p = front;
    front = front->link;
    delete p;
    // TODO: 在此处插入 return 语句
    return *this;
}

template<class T>
Chain<T>& Chain<T>::Delete(int k, T & x)
{
    if (k < 1 || !first) throw OutOfBounds();
    Node<T> *p = first;
    if (k == 1) first = first->link;
    else {
        Node<T> *q = first;
        for (int index = 1; index < k - 1 && q; index++) {
            q = q->link;
        }
        if (!q || !q->link) throw OutOfBounds(); // 不存在第k个元素
        p = q->link;
        q->link = p->link;
    }
    x = p->data;
    delete p;
    // TODO: 在此处插入 return 语句
    return *this;
}

template <class T>
int Chain<T>::Length() const
{
    Node<T> *current = first;
    int len = 0;
    while(current) {
        len++;
        current = current->link;
    }
    return len;
}
template <class T>
int Chain<T>::Search (const T&x) const
{ //寻找x，如果发现x则返回x的地址
    Node<T> *current = first;
    int index = 1;
    while (current && current->data != x)
    {
        current = current->link;
        index++;
    }
    if (current) return index;
    return 0;

}
template<class T>
Chain<T>& Chain<T>::Insert(int k, const T & x)
{
    if (k < 0) throw OutOfBounds();
    Node<T> *p = first;
    for (int i = 1; i < k&&p; i++) p = p->link;
    if (k > 0 && !p) throw OutOfBounds();
    Node<T> *y = new Node<T>;
    y->data = x;
    if (k) {
        y->link = p->link;
        p->link = y;
    }
    else {
        // 作为第一个节点插入
        y->link = first;
        first = y;
    }
    // TODO: 在此处插入 return 语句
    return *this;
}

template<class T>
Chain<T>& Chain<T>::Delete(T & x)
{
    Node<T> *p, *q;
    p = first;
    q = first;
    if (p->data != x) {
        p = p->link;
    }
    else {
        first = first->link;
        delete p, q;
        return *this;
    }
    while (p->data != x&&p) {
        p = p->link;
        q = q->link;
    }
    q->link = p->link;
    delete p;
    // TODO: 在此处插入 return 语句
    return *this;
}
template <class T>
class AdjacencyWDigraph {
    template <class T>friend class AdjacencyWGraph;
public:
    AdjacencyWDigraph(int Vertices = 10, T noEdge = 0);
    bool Exist(int i, int j) const;
    int Edges() const { return e; }
    int Vertices() const { return n; }
    AdjacencyWDigraph<T>& Add(int i, int j, const T& w);
    AdjacencyWDigraph<T>& Delete(int i, int j);
    int OutDegree(int i) const;
    int InDegree(int i) const;
    void BFS(int v, int reach[], int label);
    int *pos;
    void InitializePos() { pos = new int[n + 1]; }
    void DeactivatePos() { delete[]pos; }
    int Begin(int i); // 返回第一个与顶点i邻接的顶点
    int NextVertex(int i); // 返回下一个与顶点i邻接的顶点
    void DFS(int v, int reach[], int label);
    void dfs(int v, int reach[], int label);
    void ShortestPaths(int s, T d[], int p[]);


private:
    T NoEdge;   // 用于没有边存在的情况
    int n;   //顶点数目
    int e;   // 边数
    T **a;   // 二维数组
};

template <class T>
AdjacencyWDigraph <T>::AdjacencyWDigraph(int Vertices, T noEdge)
{
    n = Vertices;
    e = 0;
    NoEdge = noEdge;
    Make2DArray(a, n + 1, n + 1);
    //初始化没有边的图
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = NoEdge;
        }
    }
}
template <class T>
bool AdjacencyWDigraph<T>::Exist(int i, int j) const
{ // 边(i,j)存在吗
    if (i<1 || j<1 || i>n || j>n || a[i][j] == NoEdge) return false;
    return true;
}

template<class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Add(int i, int j, const T & w)
{
    if (i<1 || j<1 || i>n || j>n || a[i][j] != NoEdge) throw BadInput();
    a[i][j] = w;
    e++;
    // TODO: 在此处插入 return 语句
    return *this;
}
template <class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Delete(int i, int j)
{ // 删除边(i,j)
    if (i<1 || j<1 || i>n || j>n || a[i][j] != NoEdge) throw BadInput();
    a[i][j] = NoEdge;
    e--;
    return *this;
}
template<class T>
int AdjacencyWDigraph<T>::OutDegree(int i) const
{ //返回顶点的i的出度
    if (i<1 || i>n) throw BadInput();
    // 计算顶点i的出度
    int sum = 0;
    for (int j = 1; j <= n; j++) {
        if (a[i][j] != NoEdge) sum++;
    }
    return sum;
}
template <class T>
int AdjacencyWDigraph<T>::InDegree(int i) const
{ // 返回顶点i的入度
    if (i<1 || i>n) throw BadInput();
    // 返回顶点i的入度
    int sum = 0;
    for (int j = 1; j <= n; j++) {
        if (a[j][i] != NoEdge) sum++;
    }
    return sum;
}

template<class T>
void AdjacencyWDigraph<T>::BFS(int v, int reach[], int label)
{ // 宽度优先搜索
    LinkedQueue<int> Q;
    reach[v] = label;
    Q.Add(v);
    while (!Q.IsEmpty()) {
        int w;
        Q.Delete(w); // 获取一个已标记的顶点
                     // 对尚未标记的，邻接自w的顶点进行标记
        for (int u = 1; u <= n; u++) {
            if (a[w][u] != NoEdge && !(reach[u] == label)) {
                Q.Add(u); // u 未被标记
                reach[u] = label;
            }
        }
        if (Q.IsEmpty()) { cout << w; break; }
        cout << w << ",";
    }

}

template<class T>
int AdjacencyWDigraph<T>::Begin(int i)
{
    if (i<1 || i>n) throw OutOfBounds();
    //查找第一个邻接的顶点
    for (int j = 1; j <= n; j++) {
        if (a[i][j] != NoEdge) { //j是第一个
            pos[i] = j;
            return j;
        }
    }
    pos[i] = n + 1; // 没有邻接顶点
    return 0;
}

template<class T>
int AdjacencyWDigraph<T>::NextVertex(int i)
{
    if (i<1 || i>n) throw OutOfBounds();
    // 寻找下一个与顶点i邻接的顶点
    for (int j = pos[i] + 1; j <= n; j++) {
        if (a[i][j] != NoEdge) { //j是下一个顶点
            pos[i] = j;
            return j;
        }
    }
    pos[i] = n + 1; // 不存在下一个顶点
    return 0;
}

template<class T>
void AdjacencyWDigraph<T>::DFS(int v, int reach[], int label)
{ //深度优先搜索
    InitializePos(); //初始化图遍历器数组
    dfs(v, reach, label); // 执行dfs
    DeactivatePos(); // 释放图遍历器数组
}

template<class T>
void AdjacencyWDigraph<T>::dfs(int v, int reach[], int label)
{ // 实际执行深度优先搜索的代码
    reach[v] = label;
    int u = Begin(v);
    while (u) { //u邻接至v
        if (reach[u] != label) dfs(u, reach, label);
        u = NextVertex(v);
    }
}

template<class T>
void AdjacencyWDigraph<T>::ShortestPaths(int s, T d[], int p[])
{ //寻找从顶点s出发的最短路径， 在d中返回最短距离
  // 在p中返回前继顶点
    if (s<1 || s>n) throw OutOfBounds();
    Chain<int> L; // 路径可到达顶点的列表
    ChainIterator<int>l;
    // 初始化d,p,L
    for (int i = 1; i <= n; i++) {
        d[i] = a[s][i];
        if (d[i] == NoEdge) p[i] = 0;
        else { p[i] = s; L.Insert(0, i); }
    }
    //更新d,p
    while (!L.IsEmpty())
    { //寻找具有最小d的顶点v
        int *v = l.Initialize(L);
        int *w = l.Next();   //*v, *w是节点的标号
        while (w) {
            if (d[*w] < d[*v]) v = w;
            w = l.Next();
        }
        //从L中删除通向顶点v的下一最短路径并更新d
        int i = *v;
        L.Delete(*v);  //删除值为*v的节点
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != NoEdge && (!p[j] || d[j] > d[i] + a[i][j])) {
                //减少d[j]
                d[j] = d[i] + a[i][j];
                //将j加入L
                if (!p[j]) L.Insert(0, j);
                p[j] = i;
            }
        }
    }
}

template <class T>
class AdjacencyWGraph :public AdjacencyWDigraph<T> {
public:
    AdjacencyWGraph(int Vertices = 10, T noEdge = 0) :AdjacencyWDigraph<T>(Vertices, noEdge) {}
    AdjacencyWGraph<T>& Add(int i, int j, const T& w)
    {
        AdjacencyWDigraph<T>::Add(i, j, w);
        a[j][i] = w;
        return *this;
    }
    AdjacencyWGraph<T>& Delete(int i, int j)
    {
        AdjacencyWDigraph<T>::Delete(i, j);
        a[j][i] = AdjacencyWDigraph<T>::NoEdge;
        return *this;
    }
    int Degree(int i) const { return AdjacencyWDigraph<T>::OutDegree(i); }
};

////邻接链表存储

//template <class T>
//class LinkedBase{
//    friend class LinkedDigraph;
//    friend class LinkedGraph;
//    friend class LinkedWDigraph;
//    friend class LinkedWGraph;


//public :
//    LinkedBase(int Vertices = 10)
//    {
//        n = Vertices;
//        e = 0;
//        h = new Chain<T>[n+1]; //数组
//    }
//    ~LinkedBase(){ delete[] h;}
//    int Edges() const {return e;}
//    int Vertices() const {return n;}
//    int OutDegree(int i) const
//    {
//        if (i<1||i>n) throw OutOfBounds();
//        return h[i].Length();
//    }
//private:
//    int n ; // 顶点数
//    int e ; // 边数
//    Chain<T> *h; //邻接链表
//};
//class LinkedDigraph:public LinkedBase<int>{

//public:
//    LinkedDigraph(int Vertices = 10):LinkedBase<int>(Vertices){}
//    bool Exist(int i,int j) const;
//    LinkedDigraph& Add(int i,int j);
//    LinkedDigraph& Delete(int i,int j);
//    int InDegree(int i) const;
//protected:
//    LinkedDigraph& AddNoCheck(int i,int j);
//};
//bool LinkedDigraph::Exist(int i, int j) const
//{
//    //边(i,j)存在吗？
//    if (i<1||i>n) throw OutOfBounds();
//    return (h[i].Search(j)) ? true:false;
//}
//LinkedDigraph& LinkedDigraph::Add(int i, int j)
//{
//    if (i<1||j<1||i>n||j>n||i==j||Exist(i,j)) throw BadInput();
//    return AddNoCheck(i,j);
//}

//LinkedDigraph& LinkedDigraph::AddNoCheck(int i, int j)
//{ //增加边但不检查可能出现的错误
//    h[i].Insert(0,j); //把j添加到顶点i的链中
//    e++;
//    return *this;
//}
//LinkedDigraph& LinkedDigraph::Delete(int i, int j)
//{ //删除边(i,j)
//    if(i<1||i>n) throw OutOfBounds();
//    h[i].Delete(j);
//    e--;
//    return *this;
//}
//int LinkedDigraph::InDegree(int i) const
//{ // 返回顶点的入度
//    if(i<1||i>n) throw OutOfBounds();
//    //计算到达顶点的边
//    int sum = 0;
//    for (int j=1;j<=n;j++)
//    {
//        if (h[i].Search(i)) sum++;
//    }
//    return sum;
//}

//class LinkedGraph:public LinkedDigraph{
//public:
//    LinkedGraph(int Vertices =10) :LinkedDigraph(Vertices){}
//    LinkedGraph& Add(int i, int j);
//    LinkedGraph& Delete(int i,int j);
//    int Degree(int i) const {return InDegree(i);}
//    int OutDegree(int i) const {return InDegree(i);}
//protected:
//    LinkedGraph& AddNoCheck(int i,int j);
//};
//LinkedGraph& LinkedGraph::Add(int i, int j)
//{
//    if(i<1||i<1||i>n||j>n||i==j||Exist(i,j)) throw BadInput();
//    return AddNoCheck(i,j);
//}
//LinkedGraph& LinkedGraph::AddNoCheck(int i, int j)
//{
//    h[i].Insert(0,j);
//    try{h[j].Insert(0,i);}
//    //若出现异常，则取消第一次插入，并引发同样的异常
//    catch(OutOfBounds) {h[i].Delete(j);throw ;}
//    e++;
//    return *this;
//}
//LinkedGraph& LinkedGraph::Delete(int i, int j)
//{
//    LinkedDigraph::Delete(i,j);
//    LinkedDigraph::Delete(j,i);
//    e++;
//    return *this;
//}

//template <class T>
//class GraphNode{
//   friend class LinkedWDigraph;

//};














