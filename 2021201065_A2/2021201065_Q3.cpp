#include <iostream>
#define DSIZE 50
using namespace std;

template <typename T>
class Deque {
    int size,front,rear,count,cap=2;
    T * arr;
public:
    Deque() {
        size=DSIZE;
        arr=new T[DSIZE];
        count=0;
        front=rear=-1;  
    }
    Deque(int n,T x)
    {
        size=n*2;
        arr=new T[size];
        count=n;
        for(int i=0;i<n;i++)
            arr[i]=x;
        front=0;
        rear=n-1;
    }
    void Resize()
    {
        T * temp=arr;
        arr=new T[size*cap];
        int i=front;
        int j=0;
        while(i!=rear)
        {
            arr[j++]=temp[i];
            i=(i+1)%size;
        }
        arr[j]=temp[rear];
        front=0;
        rear=size-1;
        size=size*cap;
    }
    void Resize(int x,int d)
    {
        T * temp=arr;
        arr=new T[x*2];
        int i=front;
        int j=0;
        while(i!=rear)
        {
            arr[j++]=temp[i];
            i=(i+1)%size;
        }
        arr[j++]=temp[rear];
        front=0;
        while(j<x)
            arr[j++]=d;
        rear=x-1;
        size=x*2;
        count=x;
    }
    void Push_front(T data) {
        if((front==rear+1) || (front==0 && rear==size-1))
        {
               Resize();
        }
        
        if(isEmpty())
        {
            front=0;
            rear=0;
            arr[front]=data;
        }
        else if(front==0)
        {
            front=size-1;
            arr[front]=data;
        }
        else
        {
            front--;
            arr[front]=data;
        }
        count++;
    }
    
    void Push_back(T data) {
        if((front==rear+1) || (front==0 && rear==size-1))
        {
            Resize();
        }
        
        if(isEmpty())
        {
            front=0;
            rear=0;
            arr[rear]=data;
        }
        else if(rear==size-1)
        {
            rear=0;
            arr[rear]=data;
        }
        else
        {
            rear++;
            arr[rear]=data;
        }
        count++;
    }
    
    void Pop_front() {
        if(isEmpty())
            cout<<"Deque is Empty"<<"\n";
        else if(front==rear)
        {
            front=-1;
            rear=-1;
            count--;
        }
        else if(front==size-1)
        {
            front=0;
            count--;
        }
        else
        {
            front++;
            count--;
        }
        
    }
    
    void Pop_back() {
        if(isEmpty())
            cout<<"Deque is Empty"<<"\n";
        else if(front==rear)
        {
            front=-1;
            rear=-1;
            count--;
        }
        else if(rear==0)
        {
            rear=size-1;
            count--;
        }
        else
        {
            rear--;
            count--;
        }
    }
    
    T Front() {
        if(isEmpty())
            return -1;
        return arr[front];
    }
    
    T Back() {
        if(isEmpty())
            return -1;
        return arr[rear];
    }
    
    bool isEmpty() {
        if(front==-1 && rear==-1)
            return true;
        return false;
    }
    int Size()
    {
        return count;
    }
    void clear()
    {
        front=-1;
        rear=-1;
    }
    int operator[](int n)
    {
        n+=(front-1);
        n=(n)%size;
        return arr[n]; //add condition for if element does not exist
    }
};
int main() {
	// your code goes here
	Deque<double> d;

	d.Push_back(4);
	d.Push_back(12);
	d.Push_back(2);
	d.Push_front(19);
	d.Push_front(9);
	d.Push_front(99);
	d.Resize(10,1);
    cout<<"size"<<d.Size()<<"\n";
	cout<<"front"<<d.Front()<<"\n";
	cout<<"rear"<<d.Back()<<"\n";
	d.Pop_back();
	cout<<"size"<<d.Size()<<"\n";
	cout<<"front"<<d.Front()<<"\n";
	cout<<"rear"<<d.Back()<<"\n";
	d.Push_back(44);
	cout<<"size"<<d.Size()<<"\n";
	cout<<"front"<<d.Front()<<"\n";
	cout<<"rear"<<d.Back()<<"\n";
	d.Push_back(55);
	cout<<"size"<<d.Size()<<"\n";
	cout<<"front"<<d.Front()<<"\n";
	cout<<"rear"<<d.Back()<<"\n";
	cout<<d[3];
}
