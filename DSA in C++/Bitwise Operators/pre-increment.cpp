#include<iostream>
using namespace std;

int main(){

    int a=2, k=3;
    int pre_plus=(a+(++k)); //2 + 4 = 6!
    cout<<pre_plus<<endl; // 6, bcz it will increment the k first and then use it.


    int pre_neg=(a+(--k));//2 + 3 = 5
    cout<<pre_neg<<endl;

    return 0;

}