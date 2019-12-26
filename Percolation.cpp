#include<iostream>
#include<cstdlib>
#include<time.h>
#include "percolationStat.h"
using namespace std;

class percolation//Now my dynamic array will be initialize by n^2+2 and i will use index 1 to n only
{               // the index 0 and n^2+1 will be used by vTop and vBottom
    int *p;//matrix to be percolated
    int *size_arr;
    int n;// for dimensions of matrix
    int open_sites;
    public:
    percolation(int k)
    {
        open_sites=0;
        n=k;
        p=new int[n*n+2];
        size_arr=new int[n*n+2];
        for(int i=1;i<=n*n;i++)
        {
            p[i]=-1;
            size_arr[i]=1;

        }
        size_arr[0]=n*n+4;//this is to make the other root as node of this arr
        size_arr[n*n-1]=n*n+4;//same with this
        p[0]=0;
        p[n*n+1]=n*n+1;
    }
    ~percolation()
    {
        delete [] p;
        delete [] size_arr;
    }
    bool check(int c)
    {
        if(c<0||c>n*n+1)
        {
            cout<<"Enter right value "<<c;
            return false;
        }
        else
            return true;
    }
    int root(int id)
    {
        int root_id;
        if(!check(id))
        {
            return 0;
        }
        root_id=p[id];
        while(p[root_id]!=root_id)
        {
            root_id=p[root_id];
        }
        return root_id;
    }
    bool connected(int el1,int el2)
    {
        if(!check(el1)&&!check(el2))
        {
            return false;
        }
        int el1_root=root(el1);
        int el2_root=root(el2);
        if(el1_root==el2_root)
        {
            return true;
        }
        else
            return false;
    }
    int union_el(int el1,int el2)
    {
        if(!check(el1)||!check(el2))
        {
            return 0;
        }
        int el1_root=root(el1);
        int el2_root=root(el2);
        if(el1_root==el2_root)
        {
            return 0;
        }
        if(size_arr[el1_root]<=size_arr[el2_root])
        {
            p[el1_root]=p[el2_root];
            size_arr[el2_root]+=size_arr[el1_root];
        }
        else
        {
            p[el2_root]=p[el1_root];
            size_arr[el1_root]+=size_arr[el2_root];
        }
        return 2;
    }
    int open(int id)
    {
        if(!check(id))
        {
            return 0;
        }
        if(p[id]!=-1)
            return 0;
        else
        {
            p[id]=id;
            callUnion(id);// this function is for Conditions of square matrix and calling union
            open_sites++;
            return 1;
        }
    }
    void callUnion(int id)
    {
        if(id<=n*(n-1))
        {
          if(isopen(id+n))
            union_el(id,id+n);
        }
        else{
            union_el(id,n*n+1);
        }
        if(id>n)
        {
            if(isopen(id-n))
                union_el(id,id-n);
        }
        else{
            union_el(id,0);
        }
        if(id%n!=1)//when id is not left most end
        {
            if(isopen(id-1))
                union_el(id,id-1);
        }
        if(id%n!=0)//not rightmost end
        {
            if(isopen(id+1))
                union_el(id,id+1);
        }
    }
    bool isopen(int id)
    {
        if(!check(id))
        {
            return 0;
        }
        if(p[id]!=-1)
            return true;
        else
            return false;
    }
    bool isfull(int id)
    {
        if(root(id)==0)
        {
            return true;
        }
        else
            return false;
    }
    int numberOfOpenSites()
    {
        return open_sites;
    }
    bool percolates()
    {
        if(root(0)==root((n*n)+1))
        {
            return true;
        }
        else
            return false;
    }
    void disp()//delete
    {
        for(int i=1;i<=n*n;i++)
        {
            if(p[i]==-1)
            {
                cout<<"_ ";
            }
            else
                cout<<"O ";
            if(i%n==0)
                cout<<endl;
        }
    }
    void reset()
    {
        for(int i=1;i<=n*n;i++)
        {
            p[i]=-1;
            size_arr[i]=1;

        }
        size_arr[0]=n*n+4;
        size_arr[n*n-1]=n*n+4;
        p[0]=0;
        p[n*n+1]=n*n+1;
        open_sites=0;
    }
};
int main()
{
    int a,f;
    srand(time(0));
    cout<<"We are performing a Experiment of Percolation"<<endl;
    cout<<"Enter the dimension of square matrix"<<endl;
    cin>>a;
    int trials;
    cout<<"Enter Number of trials"<<endl;
    cin>>trials;
    percolation exp(a);
    percolationStat value(trials,a);
    for(int i=0;i<trials;i++)
    {
        bool cond=false;
        while(!cond)
        {
            f=(rand()%(a*a))+1;
            exp.open(f);
            cond=exp.percolates();
        }
        exp.disp();
        cout<<endl;
        cout<<exp.numberOfOpenSites()<<endl;
        value.init(exp.numberOfOpenSites());
        exp.reset();
    }
    cout<<"The mean of the experiment for "<<trials<<" trials is "<<value.mean()<<endl;
    cout<<"Probab is "<<(value.mean())/(a*a)<<endl;
    cout<<"The standard deviation of experiment is "<<value.stdDev()<<endl;
    cout<<"Experiment Finished"<<endl;
    value.display();
    cout<<"Press anything to quit"<<endl;
    char n;
    cin>>n;
    return 1;
}
