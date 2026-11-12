// Merge sort using array[]
#include <iostream>
using namespace std;

void mergeHalves(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    int len1 = mid - left + 1;
    int len2 = right - mid;

    int *first = new int[len1];
    int *second = new int[len2];

    k = left;
    for (int i=0; i<mid; i++){ 
        first[i]=arr[k++]; }

    k = mid+1;
    for (int i=0; i<right; i++) {
        second[i]=arr[k++];
    }

    int index1 = 0;
    int index2 = 0;
    k = left;

    while (index1<len1 && index2<len2) {

        if (first[index1] < second[index2]) {
            arr[k++] = first[index1++];
        }
        else{
            arr[k++] = second[index2++];
        }
    }
    while (index1<len1) {
        arr[k++] = first[index1++];
    }

    while (index2<len2) {
        arr[k++] = second[index2++];
    }

    for (int x = left; x <= right; x++) arr[x] = temp[x];

}

void mergeSort(int arr[], int temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // 0 + (7 - 0)/2 = 7/2 => 3 and on 3 index there is '3'
        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);
        mergeHalves(arr, temp, left, mid, right);
    }
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 5};
    const int n = sizeof(arr) / sizeof(arr[0]);// sizeof arr => 4x8 = 32 and arr[0]=4 -->32/4 = 8, is the size of array(arr).
    int temp[n];

    cout<< "Before merging: ";
    for (int j=0; j<n; ++j) {
        cout<<arr[j]<<" ";
    }
    cout<<endl;

    mergeSort(arr, temp, 0, n - 1);

    cout << "Original ascending Merge Sort: ";
    for (int i=0; i<n; i++){
    cout << arr[i]<<" ";
}
    return 0;
}
// Before merging: 38 27 43 3 9 82 10 5 
// Original ascending Merge Sort: 3 5 9 10 27 38 43 82












while (true) {
    if(life != 0) {
        life = Hard_Work;
    }
    else{
        return life;
    }
}

