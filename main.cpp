#include <stdio.h>
#include "Sort.h"

int main(){
    int arr[] = {9,8,6,7,5,2,1,3,4};
    SelectionSort(arr, sizeof(arr)/sizeof(arr[0]));

    return 0;
}