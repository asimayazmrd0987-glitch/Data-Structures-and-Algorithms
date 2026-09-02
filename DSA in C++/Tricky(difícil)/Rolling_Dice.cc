#include<iostream>
using namespace std;
#include<iomanip>
#include<cstdlib> //contain function prototype for rand

int main(){

    for (unsigned int counter{1}; counter<=20 ; ++counter){
        // pick random number from 1-6 and ouput it
        cout<< setw(10) << (1+rand()%6);

        if(counter%5==0){
            cout<<endl;
        }


    }

}


        //  2         5         4         2         6
        //  2         5         1         4         2
        //  3         2         3         2         6
        //  5         1         1         5         5
