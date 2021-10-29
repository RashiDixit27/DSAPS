#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache {
       
    class node
    {
        int key;
        int data;
        public:
        node * prev;
        node *next;    
        node(int k,int v)
        {
            key=k;
            data=v;
            prev=NULL;
            next=NULL;
        }
        void update_key(int val)
        {
            data=val;
        }
        int ret_data()
        {
            return data;
        }
        int ret_key()
        {
            return key;
        }
        
    };
public:
    unordered_map<int,node*> mp;
    int size ;
    int currsize=0;
    node * front = new node(-1,-1);
    node * rear = new node(-1,-1);
    LRUCache(int capacity) {
        size=capacity;
        front->next=rear;
        rear->prev=front;
        
    }
    void add_front(node* temp){
        temp->next=front->next;
        temp->prev=front;
        front->next->prev=temp;
        front->next=temp;
        }
    void remove_node(node * temp)
    {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
    }
    
    int get(int key) 
    {
        if(mp.find(key)==mp.end())
            return -1;
        
        node * temp= mp[key];
        remove_node(temp);
        add_front(temp);        
                   
        return temp->ret_data();
    }
    
    void set(int key, int value) 
    {
        if(mp.find(key)!=mp.end())
           {
              node * ptr =mp[key];
              ptr->update_key(value);
              remove_node(ptr);
              add_front(ptr);
              
           }
        else
           {
                node * ptr= new node(key,value);
                if(currsize < size)
                {
                    add_front(ptr);
                    mp[key]= ptr;
                    currsize++;            
                }
                else
                {
                     node * temp =rear->prev;
                     int temp_key=temp->ret_key();
                     
                     remove_node(temp);            
                     mp.erase(temp_key);
                     add_front(ptr);
                     mp[key]=ptr;
                    
                }       
             
           }
           
      return;
        
    }
};



int main()
{
    
  LRUCache * c1= new LRUCache(3);  
  c1->set(1,1);
  cout<<c1->get(3)<<"\n";
  c1->set(3,3);
  c1->set(2,2);
  cout<<c1->get(3)<<"\n";
  cout<<c1->get(3)<<"\n";  
  c1->set(4,4);
  cout<<c1->get(1)<<"\n"; 
  cout<<c1->get(2)<<"\n"; 
  return 0;  
}






