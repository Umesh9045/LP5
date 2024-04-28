
#include<iostream>
#include<omp.h>

using namespace std;

void bubbleSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=1; j<n; j++) {
            if(arr[j] < arr[j-1]) {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
}

void parallelBubbleSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        #pragma omp parallel for
        for(int j=1; j<n; j++) {
            if(arr[j] < arr[j-1]) {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = { 5, 4, 2 , 1, 7, 8, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    parallelBubbleSort(arr, n);

    cout << "\nSorted Array: \n";
    for(int i=0; i<n; i++) {
        cout << arr[i] <<"  " ;
    }

    return 0;
}

