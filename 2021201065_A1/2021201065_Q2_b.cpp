#include <iostream>
#include <unordered_map>
using namespace std;

class LFUCache {
public:
    class node
    {
        int key;
        int data;
        public:
        int freq;
        node * prev;
        node *next;    
        node(int k,int v)
        {
            key=k;
            data=v;
            freq=1;
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
    class dbll
    {
        public:
        node * front;
        node * rear;
        dbll()
        {
         front = new node(0,0);
         rear = new node(0,0);
        front->next=rear;
        rear->prev=front;
        }
        bool is_empty() 
        {
            if(  front->next==rear && rear->prev==front)
            return true;
            return false;
        }
        void add_front(node * temp)
        {
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
    };
    
    unordered_map<int, node*> mp_key;
    unordered_map<int, dbll*> mp_freq; 
    
    int minfreq=0,currsize=0,cap;
    LFUCache(int capacity) {
        cap = capacity;
    }
    
    void update_freq(node * ptr)
    {
        
        dbll * list = mp_freq[ptr->freq];
        list->remove_node(ptr);
        if(minfreq == ptr->freq && list->is_empty())
            minfreq=ptr->freq+1;
        if(mp_freq.find((ptr->freq)+1)==mp_freq.end())
        {
            dbll * nlist= new dbll();
            nlist->add_front(ptr);
            mp_freq[(ptr->freq)+1] =nlist;
        }
        else
        {
            mp_freq[(ptr->freq)+1]->add_front(ptr);
          
        }
        ptr->freq++;
    }
    
    int get(int key) {
        
        if(mp_key.find(key)==mp_key.end())
            return -1;
        node * temp =mp_key[key];
        int val =temp->ret_data();
        update_freq(temp);
        return val;
        
    }
    
    void set(int key, int value) {
        if(cap==0)
            return;
        if(mp_key.find(key)!=mp_key.end())
        {
            node * temp =mp_key[key];
            temp->update_key(value);
            update_freq(temp);   
        }
        else
        {
            if(currsize >= cap)
            {
                dbll * l =mp_freq[minfreq]; 
                node * temp =l->rear->prev;
                l->remove_node(temp);
                mp_key.erase(temp->ret_key());
                currsize--;
            }
            
            minfreq=1;
            currsize++;
            node * ptr = new node(key ,value);
            
            if(mp_freq.find(1) == mp_freq.end()) 
            {
                    dbll * nl = new dbll();
                    nl->add_front(ptr);
                    mp_freq[1] =nl;
                     
            }
            else
            {
               dbll * nl = mp_freq[1];
                nl->add_front(ptr);
            }
            
            mp_key[key]=ptr;
            }
        
    }
    
};

int main()
{
    
  LFUCache * c1= new LFUCache(3);  
  c1->set(1,1);
  cout<<c1->get(3)<<"\n";
  c1->set(3,3);
  c1->set(2,2);
  cout<<c1->get(3)<<"\n";
  cout<<c1->get(3)<<"\n";  
  c1->set(4,4);
  cout<<c1->get(1)<<"\n";  
  return 0;  
}






