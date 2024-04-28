#include <iostream>
#include <omp.h>
#include <stdlib.h>
using namespace std;

void merge(int arr[], int left, int right, int mid) {
    int i = left;
    int j = mid + 1;
    int k = left;

    int b[right + 1]; // Temporary array to store merged values

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            b[k] = arr[i];
            k++;
            i++;
        } else {
            b[k] = arr[j];
            k++;
            j++;
        }
    }

    if (i > mid) {
        while (j <= right) {
            b[k] = arr[j];
            k++;
            j++;
        }
    }

    if (j > right) {
        while (i <= mid) {
            b[k] = arr[i];
            i++;
            k++;
        }
    }

    for (k = left; k <= right; k++) {
        arr[k] = b[k];
    }
}

void mergeSort(int arr[], int left, int right) {
    // if (left < right) {
    //     int mid = left + (right - left) / 2;
    //     mergeSort(arr, left, mid);
    //     mergeSort(arr, mid + 1, right);
    //     merge(arr, left, right, mid);
    // }
    
     if (left < right) {
        int mid = left + (right - left) / 2;
        
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, left, mid);
            
            #pragma omp section
            mergeSort(arr, mid + 1, right);
        }
        merge(arr, left, right, mid);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for (int i = 0; i < arrSize; i++) {
        std::cout << arr[i] << " ";
    }

    mergeSort(arr, 0, arrSize - 1);

    std::cout << "\nSorted array: ";
    for (int i = 0; i < arrSize; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}


