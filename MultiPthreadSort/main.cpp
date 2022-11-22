#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<pthread.h>
#include<sys/time.h>
#include "Sort.h"

const int DATA_ARR_LEN = 100000;   //待排序数据的总量,数据量过大会导致栈溢出(1e7的时候)
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

    // for (int i = 0; i < PTHREAD_NUM; i++)
    // {
    //     printf("%d\n", index[i]);
    // }
    
    
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

void CalcSortTime(int dataArr[], int dataLen, void(*SortFunc)(int arr[], int len), char *sortFuncName){
    InitData(dataArr, DATA_ARR_LEN);
    struct timeval tv_begin,tv_end;
    long long s_usec;
    long long e_usec;

    printf("start %s, dataNum:%d\n", sortFuncName, dataLen);

    gettimeofday(&tv_begin,NULL);
    SortFunc(dataArr, dataLen);
    gettimeofday(&tv_end,NULL);

    s_usec = tv_begin.tv_sec * 1000000 + tv_begin.tv_usec;
    e_usec = tv_end.tv_sec * 1000000 + tv_end.tv_usec;
    printf("毫秒差: %ld\n", e_usec-s_usec);
    printf("秒差:%ld\n", (e_usec-s_usec)/1000000);  

    printf("finished\n\n");
}

int main(){    
    //算法单机
    CalcSortTime(dataArr ,DATA_ARR_LEN, SelectionSort, "SelectionSort");
    CalcSortTime(dataArr ,DATA_ARR_LEN, MergeSort, "MergeSort");
    CalcSortTime(dataArr ,DATA_ARR_LEN, QuickSortv2, "QuickSortv2");
    CalcSortTime(dataArr ,DATA_ARR_LEN, InsertionSort, "InsertionSort");
    CalcSortTime(dataArr ,DATA_ARR_LEN, ShellSort, "ShellSort");
    CalcSortTime(dataArr ,DATA_ARR_LEN, RadixSort, "RadixSort");

    //排序前的数据， 可以通过重定向来查看验证
    // printf("Before sort\n");
    // PrintArr(dataArr, DATA_ARR_LEN);
    // 测试排序的单机性能
    struct timeval tv_begin,tv_end;
    long long s_usec;
    long long e_usec;
    // gettimeofday(&tv_begin,NULL);
    // SelectionSort(dataArr, sizeof(dataArr)/sizeof(dataArr[0]));
    // // MergeSort(dataArr, sizeof(dataArr)/sizeof(dataArr[0]));
    // // QuickSort(dataArr, 0, sizeof(dataArr)/sizeof(dataArr[0])-1);
    // // ShellSort(dataArr, sizeof(dataArr)/sizeof(dataArr[0]));
    // // RadixSort(dataArr, sizeof(dataArr)/sizeof(dataArr[0]));
    // gettimeofday(&tv_end,NULL);
    // s_usec = tv_begin.tv_sec * 1000000 + tv_begin.tv_usec;
    // e_usec = tv_end.tv_sec * 1000000 + tv_end.tv_usec;
    // printf("算法单击性能\n");
    // printf("毫秒差: %ld\n", e_usec-s_usec);
    // printf("秒差:%ld\n", (e_usec-s_usec)/1000000);  
    // printf("\n");
    // PrintArr(dataArr, DATA_ARR_LEN);

    /* 多线程分布式 */
    printf("Multipthread sort start\n");
    InitData(dataArr, DATA_ARR_LEN);
    //初始化线程栏杆，PTHREAD_NUM+1是因为除了排序线程还有本进程
    pthread_barrier_init(&barrier, NULL, PTHREAD_NUM+1);
    
    gettimeofday(&tv_begin,NULL);
    for (int i = 0; i < PTHREAD_NUM; i++)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, SortWork, (void *)(i*PTHREAD_ARR_LEN));
    }
    
    pthread_barrier_wait(&barrier);
    printf("all pthread(%d) has finished\n", PTHREAD_NUM);
    pthread_barrier_destroy(&barrier);
    Merge(dataArr, DATA_ARR_LEN);

    gettimeofday(&tv_end,NULL);
    s_usec = tv_begin.tv_sec * 1000000 + tv_begin.tv_usec;
    e_usec = tv_end.tv_sec * 1000000 + tv_end.tv_usec;

    printf("毫秒差: %ld\n", e_usec-s_usec);
    printf("秒差:%ld\n", (e_usec-s_usec)/1000000);

    printf("\n");
    // printf("Merge has finished\n");
    // PrintArr(dataArr, DATA_ARR_LEN);
    
    return 0;
}