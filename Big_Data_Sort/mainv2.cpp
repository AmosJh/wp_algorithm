#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<pthread.h>
#include<sys/time.h>
#include "sortv2.h"
#include<string.h>

#define N 100

BIGINT bigdataArr[N];
//初始化数据
void InitData_big(BIGINT bigdataArr[])
{
    srand((unsigned)time(NULL));//随机数种子
    for (int i = 0; i < N; ++i) {
        BIGINT tmp_big ;
        tmp_big.digit = rand() % 102;//最多101位
        while(tmp_big.digit==0){//使得不生成位数为0的数
            tmp_big.digit = rand() % 102;
        }
        
        tmp_big.sign = rand() % 2;
        char  tmp_num[tmp_big.digit+1];
        int first = rand() % 10;
        if(first == 0){ //如果第一位是0那么这个大数就是0
            tmp_num[0]='0';
            tmp_num[1]='\0';
            tmp_big.digit = 1;//最多101位
            tmp_big.sign = 1;
        }else{ 
            tmp_num[0]='0' + first;
            for(int j = 1; j<tmp_big.digit; j++){
                int next = rand() % 10;
                tmp_num[j]='0' + next;
            }
            tmp_num[tmp_big.digit]='\0';
        }
        strcpy(tmp_big.num,tmp_num);  
        //printf("%d %d %s\n",tmp_big.sign,tmp_big.digit,tmp_big.num);
        bigdataArr[i] = tmp_big;
    }
}



int main(){
    InitData_big(bigdataArr);
    
    for (int i = 0; i < N; ++i) {
        BIGINT tmp_big = bigdataArr[i];
        printf("%d %d %s\n",tmp_big.sign,tmp_big.digit,tmp_big.num);
    }
    printf("++++++++++++++++++++++++++++++\n");
     int arrlen = N;
    //选择排序
    //SelectionSort(bigdataArr,arrlen);
    //希尔排序
    //ShellSort(bigdataArr,arrlen);
    //快排
   
    //QuickSort(bigdataArr,0,arrlen);
    //归并排序
    //MergeSort(bigdataArr,arrlen);
    //基数排序
    RadixSort(bigdataArr,arrlen);
    //printf("++++++++++++++++++++++++++++++\n");

	for (int i = 0; i < N; ++i) {
        BIGINT tmp_big = bigdataArr[i];
        if(tmp_big.sign==0)
            printf("%d -%s\n",tmp_big.digit,tmp_big.num);
        else    
            printf("%d %s\n",tmp_big.digit,tmp_big.num);
    }   
}