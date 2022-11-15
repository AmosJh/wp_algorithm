#include <stdio.h>
#include "Sort.h"

int main(){
    int arr[] = {9,8,6,7,5,2,1,3,4};
    // int arr[] = {7,6,5,4,3,2,1};
    // SelectionSort(arr, sizeof(arr)/sizeof(arr[0]));
    // MergeSort(arr, sizeof(arr)/sizeof(arr[0]));
    // QuickSort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
    ShellSort(arr, sizeof(arr)/sizeof(arr[0]));


    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    
    return 0;
}