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

void QuickSort(int arr[], int begin, int end)
{
    int i = begin, j = end;
    int curValue = arr[i];
    if( i < j)
    {
        while(i < j) {
            while (i<j && curValue<=arr[j]) 
                j--;
            if(i < j)
                arr[i++] = arr[j];
            while(i<j && arr[i]<=curValue)
                i++;
            if(i < j)
                arr[j--] = arr[i];  
        }
        arr[i] = curValue;  //找到最终位置
        // printf("找到第%d个元素的正确位置，值为:%d\n", i, arr[i]);
        QuickSort(arr, begin, i-1);
        QuickSort(arr, i+1, end);
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


void InsertionSort(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        int cur_value = arr[i];
        int cur_position = i;
        while (cur_value < arr[cur_position - 1] && cur_position > 0)
        {
            arr[cur_position] = arr[cur_position - 1];
            cur_position--;
        }
        arr[cur_position] = cur_value;

        //打印验证
        printf("第%d次排序：", i);
        for (int j = 0; j <= i; j++)
        {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}

void ShellSort(int arr[], int len)
{
    for(int gap = len/2; gap >0; gap = gap/2) {
        for (int i = gap; i < len; i++)
        {
            int cur_pos = i;
            int cur_date = arr[i];
            while(cur_pos-gap >= 0 && arr[cur_pos-gap] > cur_date){ //cur_pos-gap >= 0
                arr[cur_pos] = arr[cur_pos-gap];
                cur_pos = cur_pos - gap;
            }
            arr[cur_pos] = cur_date;
        }
    }
}