/*
 * @Author: AmosJh amos31598582@163.com
 * @Date: 2022-11-20 10:11:19
 * @LastEditors: AmosJh amos31598582@163.com
 * @LastEditTime: 2022-11-21 22:12:13
 * @FilePath: /algorithm/Sort.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __SORT_H__
#define __SORT_H__

/**
 * @brief API：选择排序。每次选取第一个未排序的数据插入到前面有序序列中
 * 
 * @param arr 待排数组
 * @param len 待排数组的长度
 */
void SelectionSort(int arr[], int len);

/**
 * @brief API：归并排序
 * 申请用于归并操作的临时数组tempMergeArr
 * 
 * @param arr 待排数组
 * @param len 待排数组的长度
 */
void MergeSort(int arr[], int len);
/**
 * @brief 归并排序辅助函数：分治
 * 
 * @param arr 待排序的数组
 * @param tempMergeArr 用于归并的临时数组
 * @param left 待排数组的左下标
 * @param right 待排数组的右下标
 */
void DivideMergeSort(int *arr, int *tempMergeArr, int left, int right);
/**
 * @brief 归并排序辅助函数：归并
 * 
 * @param arr 待排数组
 * @param tempArr 用于归并的临时数组
 * @param left 待归并数组A起始下标
 * @param middle 划分数组为A、B数组的下标
 * @param right 待归并数组B结束下标
 */
void MergeSortArr(int *arr, int *tempArr, int left, int middle, int right);

/**
 * @brief API:快速排序
 * 
 * @param arr 待排数组
 * @param begin 待排数组的起始下标
 * @param end 待排数组的结束下标
*/
void QuickSort(int arr[], int begin, int end);
void QuickSortv2(int arr[], int len);


/**
 * @brief API：插入排序
 *
 * @param arr 待排序的数组
 * @param len 数组的长度
 */
void InsertionSort(int *arr, int len);

/**
 * @brief API：希尔排序，每个制指定间隔组成的小数组使用插入排序
 *
 * @param arr 待排序的数组
 * @param len 数组的长度
 */
void ShellSort(int arr[], int len);

/**
 * @brief 基数排序辅助函数，求出最大位数
 * 
 * @param data 待排数组
 * @param len 待排数组的长度
 */
int maxbit(int data[], int len);
/**
 * @brief API：基数排序
 *
 * @param arr 待排序的数组
 * @param len 数组的长度
 */
void RadixSort(int arr[], int len);

void PrintArr(int arr[], int len);

#endif