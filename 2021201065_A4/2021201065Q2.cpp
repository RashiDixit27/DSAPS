#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <climits>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

class node{
    public:
    long long num; 
    int i;
    int j;
};
void swap(node *x, node *y)
{
    node temp = *x;
    *x = *y;
    *y = temp;
}
void min_heapify(node smallestno[],int i,int k)
{
    int left =2*i+1;
    int right = 2*i+2;
    int small=i;
    if(left<k && smallestno[small].num>smallestno[left].num)
    {
        small=left;
    }
    if(right<k && smallestno[small].num>smallestno[right].num)
    {
        small=right;
    }
    if(small!=i)
    {
        swap(&smallestno[i],&smallestno[small]);
        min_heapify(smallestno,small,k);
    }
}

void build_heap(node smallestno[],int k)
{
    for(int i=(k-1)/2;i>=0;--i)
    {
        min_heapify(smallestno,i,k);
    }
    
}

int main(int argc,char* argv[])
{
    string ipfile(argv[1]);
    string opfile(argv[2]);
    ifstream inFile;
    string line;
    int numinfile=0;
    int numbersinfile=10000000;
    int no_of_file=1;
    inFile.open(ipfile);
    ofstream outfile;
    outfile.open("temp1.txt",ios::out);
    vector <long long> vect;
    if (inFile.is_open())
    {
        while(getline(inFile,line))
        {
            stringstream linestream(line);
            string value;
            while(getline(linestream,value,','))
            {
                if(numinfile>=numbersinfile)
                {
                    no_of_file++;
                    numinfile=0;
                    string name = "temp"+to_string(no_of_file)+".txt";
                    sort(vect.begin(),vect.end());
                    for(int i=0;i<numbersinfile;i++)
                    {
                        outfile<<vect[i];
                        outfile<<"\n";
                    }
                    
                    vect.clear();
                    outfile.close();
                    outfile.open(name,ios::out);
                    if (!outfile.is_open())
                    {
                            cout<<"Cant open file";
                            exit(EXIT_FAILURE);
                    }
                }
                vect.push_back(stoll(value));
                numinfile++;
            }
        }
    }
    sort(vect.begin(),vect.end());
    for(int i=0;i<numinfile;i++)
    {
        outfile<<vect[i];
        outfile<<"\n";
    }
    vect.clear();
    outfile.close();

    string fileNames[no_of_file];
    for(int i=0;i<no_of_file;i++)
    {
        string name = "temp"+to_string(i+1)+".txt";
        fileNames[i]=name;
    }
    
    ifstream *fileObj;
    fileObj = new ifstream[no_of_file];
    if (fileObj == NULL) 
    {
        cerr << "Failed to create space for files";
        exit(EXIT_FAILURE);
    }
    for (int loopCount = 0; loopCount < no_of_file; loopCount++) 
    { 
        fileObj[loopCount].open(fileNames[loopCount],ios::in); 
        if (!fileObj[loopCount].is_open()) { 
            cerr << "Failed to open " << fileNames[loopCount] << "\n";
            for (; loopCount >= 0; loopCount--) 
            {
                fileObj[loopCount].close();
                cout << "Closed " << fileNames[loopCount] << "\n";
            }
            delete[] fileObj;
            exit(EXIT_FAILURE);
        }
    }
    outfile.open(opfile,ios::out);
    int k=no_of_file;
    node smallestno[k];
    long long temp;
    for (int i = 0; i < no_of_file; i++) 
    {
        getline(fileObj[i],line);
        temp=stoi(line);
        smallestno[i].num=temp;
        smallestno[i].i=i;
        smallestno[i].j=0;
    } 
    build_heap(smallestno,k);
    int flag=0;
    while(smallestno[0].num!=LLONG_MAX)
    {
        if(flag==0)
        {
            flag=1;
        }
        else
        {
            outfile<<",";
        }
        outfile<<smallestno[0].num;
        if((smallestno[0].i!=(k-1) && smallestno[0].j < numbersinfile-1)||(smallestno[0].i==(k-1) && smallestno[0].j < numinfile-1))
        {
            getline(fileObj[smallestno[0].i],line);
            temp=stoll(line);
            smallestno[0].num = temp;
            smallestno[0].j += 1;
        }   
        else
        {
            smallestno[0].num =  LLONG_MAX;
        }
        min_heapify(smallestno,0,k);
    }
    outfile.close();
    for (int i = (no_of_file-1); i >= 0; i--) 
    {
        fileObj[i].close();
        string name = "temp"+to_string(i+1)+".txt";
        if( remove( name.c_str() ) != 0 )
            cout<<"Error deleting file";
        
    }

    return 0;
}