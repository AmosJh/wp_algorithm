#include <stdio.h>
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

void PrintArr(int arr[], int len, int ardinal)
{
    printf("第 %d 次排序:", ardinal);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
