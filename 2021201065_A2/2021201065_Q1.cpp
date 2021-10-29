#include <iostream>
#include<climits>
using namespace std;

class compobj{
  public:
  int id;
  string val;
  compobj()
  {
      this->id=-1;
      this->val="";
  }
  compobj(int id,string val)
  {
      this->id=id;
      this->val=val;
  }

  bool operator>(compobj Ob2)
  {
      if(this->id>Ob2.id)
        return true;
      return false;
  }
  bool operator<(compobj Ob2)
  {
      if(this->id<Ob2.id)
        return true;
      return false;
  }
  bool operator==(compobj Ob2)
  {
      if(this->id==Ob2.id)
        return true;
      return false;
  }
   bool operator>=(compobj Ob2)
  {
      if(this->id>=Ob2.id)
        return true;
      return false;
  }
   bool operator<=(compobj Ob2)
  {
      if(this->id<=Ob2.id)
        return true;
      return false;
  }
  int operator -(compobj Ob2)
  {
      return this->id-Ob2.id;
  }
  friend ostream& operator<<(ostream& os, const compobj& Ob2)
    {
    os <<Ob2.id << ' ' << Ob2.val <<"\n";
    return os;
    }
};




template <typename T>
class AVLTree{
    
public:

class Node {
  public:
  T data;
  Node * left;
  Node * right;
  int height;
  int count;
  int noderst;
  int nodelst;
  Node(T data)
  {
      this->data=data;
      right=NULL;
      left=NULL;
      height=0;
      count=1;
      noderst=0;
      nodelst=0;
  }
};
Node * node;
AVLTree()
{
    node=NULL;
}
Node * left_rotate(Node * root)
    {
        Node * temp1=root->right->left;
        Node * temp2=root->right;
        root->right->left=root;
        root->right=temp1;
        int lh= (root->left==NULL)?-1:root->left->height;
        int rh= (root->right==NULL)?-1:root->right->height;
        root->height=max(lh,rh)+1;
        lh= (temp2->left==NULL)?-1:temp2->left->height;
        rh= (temp2->right==NULL)?-1:temp2->right->height;
        temp2->height=max(lh,rh)+1;
        
        if(temp1==NULL)
            root->noderst=0;
        else
            root->noderst=temp1->noderst+1;
            
        if(root==NULL)
            temp2->nodelst=0; 
        else
            temp2->nodelst=root->nodelst+1;
            
        if(temp1==NULL)
            temp2->nodelst+=0;
        else
            temp2->nodelst+=(temp1->nodelst+1);
        
        return temp2; 
    }
Node * right_rotate(Node * root)
    {
        Node * temp1=root->left->right;
        Node * temp2=root->left;
        root->left->right=root;
        root->left=temp1;
        int lh= (root->left==NULL)?-1:root->left->height;
        int rh= (root->right==NULL)?-1:root->right->height;
        root->height=max(lh,rh)+1;
        lh= (temp2->left==NULL)?-1:temp2->left->height;
        rh= (temp2->right==NULL)?-1:temp2->right->height;
        temp2->height=max(lh,rh)+1;
        
        if(root==NULL)
            temp2->noderst=0; 
        else
            temp2->noderst=root->noderst+1;
            
        if(temp1==NULL)
            temp2->noderst+=0;
        else
            temp2->noderst+=temp1->noderst+1;
        
        if(temp1==NULL)
            root->nodelst=0;
        else
            root->nodelst=(temp1->nodelst+1);
        
        
        return temp2; 
    }
    Node * insertion(Node * root, T  data)
    {
        
        if(root==NULL)
        {
            Node * ptr = new Node(data);
            return ptr;
        }
        if(root->data>data)
        {
           root->nodelst++;    
           root->left=insertion(root->left,data);
        }
        else if(root->data<data)
        {
            root->noderst++;
            root->right=insertion(root->right,data);
        }
        else if(root->data==data)
        {
            
            root->count++;
            return root;
        }
        int lh= (root->left==NULL)?-1:root->left->height;
        int rh= (root->right==NULL)?-1:root->right->height;
        root->height=max(lh,rh)+1;
        int bf= lh-rh;
        if(bf>1 && root->left->data>data)
        {
            return right_rotate(root);
        }
       
        if(bf>1 && root->left->data<data)
        {
            root->left=left_rotate(root->left);
            return right_rotate(root);
        }
        if(bf<-1 && root->right->data<data)
        {
            return left_rotate(root);
        }
        if(bf<-1 && root->right->data>data)
        {
            root->right=right_rotate(root->right);
            return left_rotate(root);
        }
        return root;
    }
    
    void display(Node * root)
    {
        if(root==NULL)
            return;
        
        display(root->left);
        for(int i=0;i<root->count;i++)
        cout<<root->data<<" ";
        display(root->right);
        
    }
    Node* deletion(Node* root, T data)
    {
        if(root==NULL)
            return NULL;
        if(root->data>data)
        {
  
            root->left=deletion(root->left,data);
        }
        else if(root->data<data)
        {

            root->right=deletion(root->right,data);
        }
        else if(root->data==data)
        {
            if(root->left==NULL && root->right==NULL )
            {
                root=NULL;
            }
            else if(root->left==NULL)
                root=root->right;
            else if(root->right==NULL)
                root=root->left;
            else
            {
                Node * temp=root->left;
                while(temp->right!=NULL)
                {
                    temp=temp->right;
                }
                root->data=temp->data;
                root->count=temp->count;
                root->left = deletion(root->left,temp->data);
                
            }
        }
        if (root == NULL)
            return root;
        int lh= (root->left==NULL)?-1:root->left->height;
        int rh= (root->right==NULL)?-1:root->right->height;
        root->height=max(lh,rh)+1;
        int bf= lh-rh;
        int bfl=0;
        if(root->left!=NULL)
        {
        int lhl= (root->left->left==NULL)?-1:root->left->left->height;
        int rhl= (root->left->right==NULL)?-1:root->left->right->height;
        bfl= lhl-rhl;
        }
        int bfr=0;
        if(root->right!=NULL)
        {
        int lhr= (root->right->left==NULL)?-1:root->right->left->height;
        int rhr= (root->right->right==NULL)?-1:root->right->right->height;
        bfr= lhr-rhr;
        }
        if(bf>1 && bfl>=0)
        {
            return right_rotate(root);
        }
        else if(bf>1 && bfl<0)
        {
            root->left=left_rotate(root->left);
            return right_rotate(root);
        }
        else if(bf<-1 && bfr<=0)
        {
            return left_rotate(root);
        }
        else if(bf<-1 && bfr>0)
        {
            root->right=right_rotate(root->right);
            return left_rotate(root);
        }
        return root;
    }
    void delete_node(T data)
    {
        if(search(data))
        node=deletion(node,data);
        return;
    }
    
    int count_occurrences(T data)
    {
        Node * root =node;
        while(root!=NULL)
        {
            if(root->data>data)
                root=root->left;
            else if(root->data<data)
                root=root->right;
            else
            {
                return root->count;
            }
        }
        return 0;
    }
    
    bool search(T data)
    {
        Node * root =node;
        while(root!=NULL)
        {
            if(root->data>data)
                root=root->left;
            else if(root->data<data)
                root=root->right;
            else
            {
                return true;
            }
        }
        return false;
    }
    
    T closest_element(T num)
    {
        Node *root=node;
        int md=INT_MAX;
        T mdd;
         while(root!=NULL)
        {
            if(root->data>num)
            {
                if(md>abs(root->data-num))
                {
                    md=abs(root->data-num);
                    mdd=root->data;
                }
                root=root->left;
            }
            else if(root->data<num)
            {
                if(md>abs(root->data-num))
                {
                    md=abs(root->data-num);
                    mdd=root->data;
                }
                root=root->right;
            }
            else
            {
                return root->data;
            }
        }
        return mdd;    
    }
    
    void lower_bound(T data)
    {
        Node * root =node;
        Node * temp= NULL;
        while(root!=NULL)
        {
            if(root->data>data)
            {
                if(temp==NULL ||temp->data>root->data)
                    temp=root;
                root=root->left;
            }
            else if(root->data<data)
            {
                root=root->right;
            }
            else
            {
                temp=root;
                break;
            }
        }
         if(temp!=NULL)
                cout<<"Lower bound"<<temp->data;
                else
                cout<<"Dosn't Exist";
        return;
    }
    
    void upper_bound(T data)
    {
        Node * root =node;
        Node * temp= NULL;
        while(root!=NULL)
        {
            if(root->data>data)
            {
                root=root->left;
            }
            else if(root->data<data)
            {
                
                if(temp==NULL ||temp->data<root->data)
                    temp=root;
                root=root->right;
            }
            else
            {
                temp=root;
                break;
            }
        }
         if(temp!=NULL)
                cout<<"Upper bound : "<<temp->data;
                else
                cout<<"Dosn't Exist";
        return;
    }
    Node * kthele(Node *root,int& k)
    {
    	if(root==NULL || k==0)
			return root;
	
		else if( k-1 == root->noderst ){
			return root;
			
		}
		else if( k > root->noderst ){
			k =k-1- root->noderst;
			return kthele(root->left, k);
		}
		else if( k == root->noderst ){
			k -= root->noderst;
			return kthele(root->right, k);
		}
		else{
			return kthele(root->right, k);	
		}
    }
 
    void Kthlargestele(int K)
    {
        if(K<=0)
        {
            cout<<"Kth element not present";
            return ;
        }
        Node * temp=kthele(node, K);
        if(temp==NULL)
        {
            cout<<"Kth element not present";
        }
        else
        cout<<"Kth largest element:"<<temp->data;
        return ;
    }
    
    int countrange(Node * root, T lo, T hi)
    {
    if (root == NULL) {
        return 0;
    }
    if (root->data >= lo && root->data <= hi) {
        return root->count + countrange(root->left, lo, hi) + countrange(root->right, lo, hi);
    } else {
        if (root->data < lo) {
            return countrange(root->right, lo, hi);
        } else {
            return countrange(root->left, lo, hi);
        }
    }
    }
    
    void countrangeele(T lo,T hi)
    {
        cout<<"Elements in range :"<<countrange(node, lo, hi);
        return ;
    }
    
    
    
};


int main() {
	int i;
	cin>>i;
	AVLTree<char> ob;
	while(i--)
	{
	  char n;
	  cin>>n;
	  ob.node = ob.insertion(ob.node,n);
	  ob.display(ob.node);
	  cout<<"\n";
	}
	cout<<ob.count_occurrences('m');
	cout<<ob.count_occurrences('b');
	ob.delete_node('a');
	cout<<ob.count_occurrences('a');
	cout<<ob.count_occurrences('b');
 
	ob.display(ob.node);
	cout<<"\n";
	
	cout<<ob.count_occurrences('g');
	ob.display(ob.node);
	cout<<ob.search('g');
	cout<<ob.search('d');
    cout<<ob.closest_element('q');
    cout<<ob.closest_element('f');
    cout<<ob.closest_element('z');
    ob.lower_bound('z');
    cout<<"\n";
    ob.lower_bound('a');
    cout<<"\n";
    ob.upper_bound('e');
    cout<<"\n";
    ob.upper_bound('z');
    cout<<"\n";
    ob.upper_bound('a');
    cout<<"\n";
    ob.lower_bound('e');
    ob.Kthlargestele(2);
    ob.countrangeele('b','p');
    compobj ob1(1,"Hello");
    compobj ob2(2,"hii");
    compobj ob3(3,"hii");
    compobj ob4(4,"hii");
    compobj ob5(5,"hii");
    compobj ob6(6,"hii");
    AVLTree<compobj> t2;
    t2.node = t2.insertion(t2.node,ob1);
    t2.node= t2.insertion(t2.node,ob2);
	t2.display(t2.node);    
	t2.node= t2.insertion(t2.node,ob3);
	t2.node= t2.insertion(t2.node,ob4);
	t2.node= t2.insertion(t2.node,ob5);
	t2.display(t2.node);    
	cout<<t2.search(ob4);
	cout<<t2.search(ob6);
	t2.node= t2.insertion(t2.node,ob5);
	cout<<t2.count_occurrences(ob5);
	t2.delete_node(ob3);
	t2.delete_node(ob6);	
	t2.display(t2.node); 
	cout<<t2.closest_element(ob6);
    cout<<t2.closest_element(ob3);
    t2.lower_bound(ob3);
    cout<<"\n";
    t2.upper_bound(ob3);
    t2.Kthlargestele(3);
    t2.countrangeele(ob2,ob4);	
	return 0;
}

