#include<iostream>
using namespace std;

template <typename T>
class Myvector{
	T* arr;
	int capacity;
	int current;
	public:
		
		Myvector() {
			arr = new T[1];
			capacity=1;
			current=0;
		}
		
		Myvector(int size) {
			arr = new T[size];
			capacity=size;
			current=0;
		}
		// function to push element in a vector
		void push_back(T data)                               //worstcase = O(n) or Amortized O(1)
		{
			if(current == capacity)
			{
				capacity = capacity*2;
				T *temp  =  new T[capacity];
				
				for (int i = 0; i < current; i++)
				{
					temp[i] = arr[i];
				}
				
			delete[] arr;
			arr = temp;
				
			}
			arr[current]=data;
			current++;
			
		}
	     // function to remove last element
	    void pop_back(){                                  // O(1)
	    	if(current == 0){
	    		cout<<"Empty - no element stored in vecor";
	    		return;
			}
			current--;
	    	
		}
	    
		void insert(int index,T data){
			if(index < 0 || index > current){
				return;
			}
			if(current == capacity)
			{
				capacity = capacity*2;
				T *temp  =  new T[capacity];
				
				for (int i = 0; i < current; i++)
				{
					temp[i] = arr[i];
				}
				
			delete[] arr;
			arr = temp;
				
			}
			for(int i = current-1; i >= index ; i -- ){
				arr[i+1] = arr[i];
			}
			arr[index]= data;
			current++;
		}
		// function to erase element at any index
	   void erase(int index){                            // O(1)
	   	if (current == 0 || index < 0 || index >= current){
	   		cout<<"invalid index"<<endl;
	   			return;
		   }
		 for(int i = index ; i < current-1 ; i++){
		 	arr[i] = arr[i+1];
		 }
		 current--;  
	   }
	   //function to return the size
	   int size(){
	   	 return current;
	   }
	   int get_capacity(){
	   	return capacity;  	
	   }
	   bool empty(){
	   	if(current == 0){
	   		return true;
		   }
		return false;
	   }
	   void clear(){
	   	current = 0;
	   }
	   T front(){
	   	if(current == 0){
	   		return T();
		   }
		return arr[0];   
	   }
	   T back(){
	   	if(current == 0){
	   		return T();
		   }
		return arr[current-1];   
	   }
	   
//	    T& front(){       // programmer promises that i will not call to an empty vector
//		 return arr[0];    //advanced stl
//	   }
//	
       T& operator[](int index){
       	 return arr[index];
	   }

		//function to print all the data of vector     
		void print(){                                  //worst case = O(n)
			if(current == 0 )                           
			{
				cout<<"Empty"<<endl;
				return;
			}
			for(int i = 0; i < current ; i++)
			{
				cout<<arr[i]<<" ";
			}
			cout<<endl;
		}
		~Myvector(){
			delete[]arr;
		}		
};
int main(){
	Myvector<int> v;
	cout<<"front "<<v.front()<<endl;
	v.print();
	cout<<"capacity = "<< v.get_capacity()<<endl;
	v.push_back(10);
	v.push_back(20);
	v.print();
	cout<<"capacity = "<< v.get_capacity()<<endl;
	v.push_back(30);
	v.insert(2,200);
	v.print();
	cout<<"capacity = "<< v.get_capacity()<<endl;
	v.push_back(40);
	v.print();
	cout<<"capacity = "<< v.get_capacity()<<endl;
	v.push_back(50);
	v.print();
	cout<<"size = "<< v.size()<<endl;
	cout<<"capacity = "<< v.get_capacity()<<endl;
	v.pop_back();
	v.erase(0);
	v.insert(1,100);
	v.print();
	cout<<"size = "<< v.size()<<endl;
	cout<<"capacity = "<< v.get_capacity()<<endl;
	cout<<"front "<<v.front()<<endl;
	cout<<"back "<<v.back()<<endl;
	cout<<v[2]<<endl;
	cout<<v[1];
	}
