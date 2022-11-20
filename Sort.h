/*
 * @Author: AmosJh amos31598582@163.com
 * @Date: 2022-11-20 10:11:19
 * @LastEditors: AmosJh amos31598582@163.com
 * @LastEditTime: 2022-11-20 19:46:19
 * @FilePath: /algorithm/Sort.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __SORT_H__
#define __SORT_H__

void SelectionSort(int arr[], int len);

/**
 * @brief API：采用分治的归并排序
 * 申请用于归并操作的临时数组tempMergeArr
 * 
 * @param arr 待排数组
 * @param len 待排数组的长度
 */
void MergeSort(int arr[], int len);
/**
 * @brief 分治归并操作
 * 
 * @param arr 待排序的数组
 * @param tempMergeArr 用于归并的临时数组
 * @param left 待排数组的左下标
 * @param right 待排数组的右下标
 */
void DivideMergeSort(int *arr, int *tempMergeArr, int left, int right);
/**
 * @brief 归并操作
 * 
 * @param arr 待排数组
 * @param len 待排数组的长度
 */
void MergeSortArr(int *arr, int *tempArr, int left, int middle, int right);

void QuickSort(int arr[], int begin, int end);

/**
 * @brief 插入排序
 *
 * @param arr 待排序的数组
 * @param len 数组的长度
 */
void InsertionSort(int *arr, int len);
void ShellSort(int arr[], int len);

/**
 * @brief 基数排序辅助函数，求出最大位数
 * 
 * @param data 待排数组
 * @param len 待排数组的长度
 */
int maxbit(int data[], int len);
void RadixSort(int arr[], int len);

void PrintArr(int arr[], int len);

#endif