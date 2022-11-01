#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sort.h"

void SelectionSort(int arr[], int len)
{
        for (int i = 0; i < len; i++)
        {
            int minValue = arr[i];
            int minIndex = i;
            for (int j = i+1; j < len; j++)
            {
                if (arr[j] < minValue)
                {
                    minValue = arr[j];
                    minIndex = j;
                }
                
            }
            
            arr[minIndex] = arr[i];
            arr[i] = minValue;

            PrintArr(arr, len, i);            
        }
}

void MergeSort(int arr[], int len)
{
    int* tempMergeArr = (int*)malloc(sizeof(int) * len);
    if (tempMergeArr == NULL)
    {
        fprintf(stderr, "malloc error!\n");
        return;
    }
    memset(tempMergeArr, 0, len);

    DivideMergeSort(arr, tempMergeArr, 0, len-1);

    if (tempMergeArr != NULL)
    {
        free(tempMergeArr);
        tempMergeArr = NULL;
    }
}
void DivideMergeSort(int *arr, int *tempMergeArr, int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        DivideMergeSort(arr, tempMergeArr, left, middle);
        DivideMergeSort(arr, tempMergeArr, middle + 1, right);
        MergeSortArr(arr, tempMergeArr, left, middle, right);
    }
}
void MergeSortArr(int *arr, int *tempArr, int left, int middle, int right)
{
    int i = left;
    int j = middle + 1;
    int tempArrPosition = 0;
    while (i <= middle && j <= right)
    {
        tempArr[tempArrPosition++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
    }
    while (i <= middle)
    {
        tempArr[tempArrPosition++] = arr[i++];
    }
    while (j <= right)
    {
        tempArr[tempArrPosition++] = arr[j++];
    }

    for (int i = 0; i < tempArrPosition; i++)
    {
        arr[left + i] = tempArr[i];
    }
}

void PrintArr(int arr[], int len, int ardinal)
{
    printf("第 %d 次排序:", ardinal);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
