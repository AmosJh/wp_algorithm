#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 插入排序
 *
 * @param arr 待排序的数组
 * @param len 数组的长度
 */
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

/**
 * @brief 
 * 
 * @param arr 待排数组
 * @param tempArr 用于归并的临时数组
 * @param left 待排数组的左下标
 * @param middle 待排数组的中间
 * @param right 待排数组的右下标
 */
void mergeSortArr(int *arr, int *tempArr, int left, int middle, int right)
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

/**
 * @brief 将数组分治为左右两个数组，并分别递归调用该方法，最后进行归并
 * 
 * @param arr 待排序的数组
 * @param tempArr 用于归并的临时数组
 * @param left 待排数组的左下标
 * @param right 待排数组的右下标
 */
void InternalMergeSort(int *arr, int *tempArr, int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        InternalMergeSort(arr, tempArr, left, middle);
        InternalMergeSort(arr, tempArr, middle + 1, right);
        mergeSortArr(arr, tempArr, left, middle, right);
    }
}

/**
 * @brief 左右数组归并方法
 * 
 * @param arr 待排数组
 * @param len 待排数组的长度
 */
void MergeSort(int* arr, int len)
{
    int* tempArr = (int*)malloc(sizeof(int) * len);
    if (tempArr == NULL)
    {
        fprintf(stderr, "malloc error!\n");
        return;
    }
    memset(tempArr, 0, len);

    InternalMergeSort(arr, tempArr, 0, len-1);

    if (tempArr != NULL)
    {
        free(tempArr);
        tempArr = NULL;
    }
}

int main()
{
    int arr[] = {4, 3, 2, 1};
    InsertionSort(arr, sizeof(arr) / sizeof(arr[0]));

    int arr2[] = {12, 8, 16, 3, 5, 11, 9, 6};
    MergeSort(arr2, sizeof(arr2)/sizeof(arr2[0]));
    
    // for (int i = 0; i < sizeof(arr2)/sizeof(arr2[0]); i++)
    // {
    //     printf("%d ", arr2[i]);
    // }
    // printf("\n");
    
    return 0;
}

