#include "percolationStat.h"//error in standard deviation
#include<cmath>
#include<iostream>
using namespace std;
percolationStat::percolationStat(int t,int a)
{
    n=a;// dimensions of square matrix created
    arr=new int[t];
    for(int i=0;i<t;i++)
        arr[i]=0;
    trials=t;
    avg=0.0;
    dev=0.0;
}
percolationStat::~percolationStat()
{
    delete []arr;
}
void percolationStat::init(int k)
{
    static int p=0;
    arr[p]=k;
    p++;
}
double percolationStat::mean()
{
    avg=0.0;        //initializing it to get the right value whenever we call it
    for(int n=0;n<trials;n++)
    {
        avg=avg+arr[n]/trials;
    }
    return avg;
}
double percolationStat::stdDev()
{
    for(int i=0;i<trials;i++)
    dev=dev+sqrt(pow((arr[i]-avg),2)/trials);
    return this->dev;
}
void percolationStat::display()
{
    for(int i=0;i<trials;i++)
        cout<<arr[i]<<endl;
}
