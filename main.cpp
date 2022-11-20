#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<pthread.h>
#include<sys/time.h>
#include "Sort.h"

const int DATA_ARR_LEN = 1e6;   //待排序数据的总量,数据量过大会导致栈溢出(1e7的时候)
const int MAX_DATA_VALUE = 1e7;  //待排数据中的数据最大值
const int PTHREAD_NUM = 4;    //线程的数量(数组的数量)
const int PTHREAD_ARR_LEN = DATA_ARR_LEN/PTHREAD_NUM;   //每个线程内元素的数量

int dataArr[DATA_ARR_LEN];

pthread_barrier_t barrier;

//初始化数据
void InitData(int dataArr[], int dataLen)
{
    srand((unsigned)time(NULL));//随机数种子
    for (int i = 0; i < dataLen; ++i) {
        dataArr[i] = rand() % MAX_DATA_VALUE;
    }
}

void* SortWork(void* startIndex)
{
    int endIndex = (long)startIndex+PTHREAD_ARR_LEN-1;
    if (endIndex >= DATA_ARR_LEN)
    {
        endIndex = DATA_ARR_LEN - 1;
    }

    QuickSort(dataArr, (long)startIndex, endIndex);
    
    printf("%d has finished\n", (long)startIndex);
    pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
}

//除了快排外的通用排序
void* SortWorkv2(void* startIndex)
{
    ShellSort(dataArr+(long)startIndex, PTHREAD_ARR_LEN);
    
    printf("%d has finished\n", (long)startIndex);
    pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
}

void Merge(int arr[], int arrLen)
{
    int tmpArr[DATA_ARR_LEN] = {0};
    int minIndex = 0;//记录当前选取最小的元素所属的归并数组序号
    // int minData = MAX_DATA_VALUE+1;

    int index[PTHREAD_NUM] = {0}; //index[i]的值，指向第i个数组未归并的第一个元素
    for (int i = 0; i < PTHREAD_NUM; i++)
    {
        index[i] = i * PTHREAD_ARR_LEN;
    }

    for (int i = 0; i < PTHREAD_NUM; i++)
    {
        printf("%d\n", index[i]);
    }
    
    
    for (int i = 0; i < DATA_ARR_LEN; i++)//DATA_ARR_LEN个数据进行归并
    {
        int minData = MAX_DATA_VALUE+1;
        //从所有数组中选出一个最小值
        for (int j = 0; j < PTHREAD_NUM; j++)
        {
            if (index[j] >= PTHREAD_ARR_LEN*(j+1))
            {
                continue;
            }
            if (index[j] == DATA_ARR_LEN)
            {
                continue;
            }
            
            
            if (arr[index[j]] < minData)
            {
                minData = arr[index[j]];
                minIndex = j;
            }
        }
        index[minIndex]++;
        tmpArr[i] = minData;
        // printf("tmpArr[%d]=%d\n", i, tmpArr[i]);
    }

    for (int i = 0; i < arrLen; i++)
    {
        arr[i] = tmpArr[i];
    }
    
}

int main(){

    // int arr[] = {9,8,6,7,5,2,1,3,4};
    // int arr[] = {7,6,5,4,3,2,1};
    // int arr[] = {9,18,26,37,105,21,17,336,4021};
    // int arr[100] = {0};

    // SelectionSort(arr, sizeof(arr)/sizeof(arr[0]));
    // MergeSort(arr, sizeof(arr)/sizeof(arr[0]));
    // QuickSort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
    // ShellSort(arr, sizeof(arr)/sizeof(arr[0]));
    // RadixSort(arr, sizeof(arr)/sizeof(arr[0]));
    // PrintArr(dataArr, DATA_ARR_LEN);
    
    InitData(dataArr, DATA_ARR_LEN);
    //排序前的数据， 可以通过重定向来查看验证
    // printf("Before sort\n");
    // PrintArr(dataArr, DATA_ARR_LEN);
    
    //初始化线程栏杆，PTHREAD_NUM+1是因为除了排序线程还有本进程
    pthread_barrier_init(&barrier, NULL, PTHREAD_NUM+1);

    struct timeval tv_begin,tv_end;
    gettimeofday(&tv_begin,NULL);
    for (int i = 0; i < PTHREAD_NUM; i++)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, SortWorkv2, (void *)(i*PTHREAD_ARR_LEN));
    }
    
    pthread_barrier_wait(&barrier);
    printf("all pthread has finished\n");
    printf("\n");
    pthread_barrier_destroy(&barrier);
    Merge(dataArr, DATA_ARR_LEN);

    gettimeofday(&tv_end,NULL);
    long long s_usec = tv_begin.tv_sec * 1000000 + tv_begin.tv_usec;
    long long e_usec = tv_end.tv_sec * 1000000 + tv_end.tv_usec;
    printf("毫秒差: %ld\n", e_usec-s_usec);
    printf("秒差:%ld\n", (e_usec-s_usec)/1000000);

    printf("\n");
    // printf("Merge has finished\n");
    // PrintArr(dataArr, DATA_ARR_LEN);
    
    return 0;
}