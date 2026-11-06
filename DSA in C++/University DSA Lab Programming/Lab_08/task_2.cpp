
#include <iostream>
#include <string>
using namespace std;

// Structure to store student information
struct Student {
    string name;
    int marks;
};

// Merge two sorted halves in descending order
void mergeHalves(Student arr[], Student temp[],
                 int left, int mid, int right) {

    int i = left;
    int j = mid + 1;
    int k = left;

    // Merge both halves
    while (i <= mid && j <= right) {

        // >= preserves the original order when marks are equal
        if (arr[i].marks >= arr[j].marks) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    // Copy remaining elements from left half
    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    // Copy remaining elements from right half
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // Copy merged elements back into original array
    for (int x = left; x <= right; x++) {
        arr[x] = temp[x];
    }
}

// Recursive Merge Sort function
void mergeSort(Student arr[], Student temp[],
               int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        // Sort left half
        mergeSort(arr, temp, left, mid);

        // Sort right half
        mergeSort(arr, temp, mid + 1, right);

        // Merge both sorted halves
        mergeHalves(arr, temp, left, mid, right);
    }
}

// Display merit list
void printMeritList(Student arr[], Student temp[], int n) {

    mergeSort(arr, temp, 0, n - 1);

    cout << "\n----------------------------------\n";
    cout << "             MERIT LIST\n";
    cout << "----------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". "
             << arr[i].name << " "
             << arr[i].marks << endl;
    }

    cout << "----------------------------------\n";
}

int main() {

    // Test Case 1: Given class list
    Student class1[5] = {
        {"Ali", 72},
        {"Sara", 90},
        {"Bilal", 72},
        {"Hina", 85},
        {"Zain", 60}
    };

    Student temp1[5];

    cout << "\nTEST CASE 1: ORIGINAL CLASS LIST";
    printMeritList(class1, temp1, 5);


    // Test Case 2: Another class list
    Student class2[5] = {
        {"Zara", 88},
        {"Ahmed", 95},
        {"Saad", 88},
        {"Maryam", 76},
        {"Usman", 95}
    };

    Student temp2[5];

    cout << "\nTEST CASE 2: SECOND CLASS LIST";
    printMeritList(class2, temp2, 5);


    // Test Case 3: All students have equal marks
    Student class3[5] = {
        {"Ayan", 82},
        {"Hira", 82},
        {"Omar", 82},
        {"Laiba", 82},
        {"Hamza", 82}
    };

    Student temp3[5];

    cout << "\nTEST CASE 3: ALL STUDENTS HAVE EQUAL MARKS";
    printMeritList(class3, temp3, 5);

    return 0;
}
