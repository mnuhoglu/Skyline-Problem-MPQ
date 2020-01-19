#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std ;
template <class Typ>
 struct HeapNode //struct for heap
 {
	 Typ value ;
     int label ;
	 HeapNode(){value=0;label=0;};
	// HeapNode(const Typ & v,const int & l):value(v),label(l) {};
 };

template <class Typ>
class BinaryHeap
{
    public:
	BinaryHeap(){};
	~BinaryHeap(){currentSize=0;for(int m=0;m<array.size();m++)	array.pop_back();for(int j=0;j<Location.size();j++)Location.pop_back();}
    BinaryHeap(int capacity){for(int i=0;i<capacity;i++)
	{HeapNode<Typ> newnode;array.push_back(newnode);}currentSize=0;for(int k=0;k<5000;k++){Location.push_back(0);} }
    void insert(const Typ & x,int label);
    Typ GetMax();
    bool isEmpty();
	Typ Remove ( int label) ;
    
    private:
    
    int currentSize; 
	vector<int> Location ;
	vector<HeapNode<Typ>> array; 
    void percolateDown( int hole ) ;

};


template <class Typ>
void BinaryHeap<Typ>::insert( const Typ & x ,int label )//inserts given node to correct plac
{
	if(currentSize == array.size() -1 )
        array.resize( array.size() * 2) ;
    
    int hole = ++currentSize;
    for( ; hole > 1 && x > array[hole/2].value  ; hole /= 2 )
	{
        array[ hole ] = array[ hole / 2 ];
		Location[array[hole].label]=hole;
	}
    array[hole].value = x;	
	array[hole].label = label;
	Location[array[hole].label]=hole;

}

template <class Typ>
void BinaryHeap<Typ>::percolateDown(int hole)//finds the correct place for given hole
{
    int child ;
    Typ temp = array[hole].value ;
	int lab= array[hole].label;
    for( ; hole*2 <=array.size() ; hole = child)
    {
        child = hole *2 ;
        
        if ( child != array.size() && ( array[child +1].value > array[child].value))
            child = child++;
        if( array[child].value > temp ) 
		{
            array[hole].value = array[ child].value ;
			array[hole].label = array[ child].label ;
			Location[array[child].label]=hole;
		}
		else
            break ;
    }
    array[hole].value = temp;
	array[hole].label = lab;
	Location[array[hole].label]=lab;
}

template <class Typ>
bool BinaryHeap<Typ>::isEmpty()//returns true if heap is empty
{
	return(currentSize==0);
}

template <class Typ>
Typ BinaryHeap<Typ>::Remove( int label)//removes given node and rearranges the heap
{
	if(isEmpty())
		return	0;
	
	array[Location[label]].label = array[currentSize].label;
	array[Location[label]].value = array[currentSize].value;
	array[currentSize].label=0;
	array[currentSize].value=0;
	currentSize--;
		percolateDown(Location[label]);
}

template <class Typ>
Typ BinaryHeap<Typ>::GetMax()//returns top of the heap
{
	if(currentSize==0)return 0;
	return array[1].value;
}