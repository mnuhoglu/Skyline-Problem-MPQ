#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "BinaryHeap.h"


using namespace std ;

enum EntryType { LEFT, RIGHT, EMPTY };
struct mystruct//struct for the vector keeps the x coordinates in descending order.
{
    EntryType direction ;
    int value ;
    int height ;
    int label ;
	mystruct(){
	direction=EMPTY;
	value=0;
	height=0;
	label=0;
	}
    mystruct(EntryType dir,int value2,int height2 ,int label2){
	direction=dir;
	value=value2;
	height=height2;
	label=label2;
	}
};

bool comparebyvalue(const mystruct & a,const mystruct & b)//this function arranges the x coordinates in descending order
{
	return a.value<b.value;
}

int main()
{
	ifstream reader ;
    reader.open("input.txt") ;
    string input ;
    reader>>input ; 
    int NumberofBuildings = stoi(input) ;

	int leftC,rightC,height;
	int label = 0;

	vector<mystruct> myvec;

	while(getline(reader,input))//inputs pushed to vector;lefts and rights pushed seperately
	{
		if(input!="")
		{
		label++;
		istringstream iss(input);
		iss >> leftC >> height >> rightC;
		mystruct comingbuilding;	
		comingbuilding.direction = LEFT;
		comingbuilding.label = label;
		comingbuilding.value = int(leftC);
		comingbuilding.height = height;

		myvec.push_back(comingbuilding);

		comingbuilding.direction = RIGHT;
		comingbuilding.value = int(rightC);
		myvec.push_back(comingbuilding);
		}
	}

	sort(myvec.begin(),myvec.end(),comparebyvalue);
	BinaryHeap<int> myheap(myvec.size());
	int prevmax=0;
	for(int i=0;i < myvec.size(); i++)
	{
		if(i==0 && myvec[i].value > 0 )
			cout << "0 0" << endl;
		
		
		
	
 		if(myvec[i].direction == LEFT)
			myheap.insert(myvec[i].height,myvec[i].label);
		else if(myvec[i].direction == RIGHT)
			myheap.Remove(myvec[i].label);
			
		/*if(myheap.GetMax() != prevmax)
			cout << myvec[i].value << " " << myheap.GetMax() << endl;*/
	
		if(i<myvec.size()-1)
		{
			if(myvec[i].value!=myvec[i+1].value )
				if(myheap.GetMax()!=prevmax)
				{
					prevmax = myheap.GetMax();
					cout<<myvec[i].value<<" " <<myheap.GetMax()<<endl;
				}
		}
		else
		{
			if(myheap.GetMax()!=prevmax)
			{
				prevmax = myheap.GetMax();
				cout<<myvec[i].value<<" " <<myheap.GetMax()<<endl;
			}
		}
	}


	return 0;
}