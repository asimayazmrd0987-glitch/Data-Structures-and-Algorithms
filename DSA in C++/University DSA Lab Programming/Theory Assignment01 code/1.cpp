#include<iostream>
using namespace std;


int main(){

    int k = 805;
    int A[8];
    // loop for printing and assigning the values into an array A.
    for(int i = 0 ; i < 8 ; i++){
        // calculating all the element using the formula
      A[i] = ((((13*k) + (17*i) + (i*i)) % 90) + 10);
      cout<<"Element at index "<<i<<" "<<A[i]<<endl; 
    }


    //here we calculate the value for t now we will search it through loop
    int T = A[(k+2)%8];
    cout<<"T: "<<T<<endl;
    //this loop will also count the comparisons and will return the position of the value T
    int comp = 0;
    int position=-1;
     for(int i = 0; i<8 ; i++){
       comp++;
      if(T == A[i]){
        position = i;
        break;
      }
    
     }
     cout<<"Position of T: "<<position<<endl;
     cout<<"Comparision: "<<comp<<endl;   

                                 //part c
     // here find the value x
     int  X = (((7*k)+11)%90)+10;
     cout<<"X: "<<X<<endl;
     // here we the index p
     int p = k % 8;
     cout<<"index p: "<<p<<endl;
     // here we shifting the element of the array and 
     // create space for index p

     for(int i = 7; i >= p ; i--){
      A[i] = A[i-1];
      //this condition insert the value at index p
      if(i == p){
        A[i] = X;
      }
     }
    //print the updated array
     for(int i = 0; i < 8; i++){
       cout<<"Element at index "<<i<<" "<<A[i]<<endl; 
     }

           
                                              //part d
     cout<<"\n\n"<<endl;
     cout<<" __________________Part D_________________ "<<endl;                            
       // find the index q                         
      int q = (k+5) % 9;
      cout<<"index q: "<<q<<endl;
      //delete or override the value at index q and shift all
      //                        the value toward the q after the it.
      for(int i = q; i < 8 - 1 ; i++){
       A[i] = A[i+1];
      }
      //print the updated array
     for(int i = 0; i < 8-1; i++){
       cout<<"Element at index "<<i<<" "<<A[i]<<endl; 
     }

}