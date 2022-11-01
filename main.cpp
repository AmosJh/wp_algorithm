#include <stdio.h>
#include "Sort.h"

int main(){
    int arr[] = {9,8,6,7,5,2,1,3,4};
    // SelectionSort(arr, sizeof(arr)/sizeof(arr[0]));
    MergeSort(arr, sizeof(arr)/sizeof(arr[0]));
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    
    return 0;
}