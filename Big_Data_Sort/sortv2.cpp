#include "sortv2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//比较函数
int cmp(BIGINT a , BIGINT b){//返回0则相等，返回1则a>b，返回-1则a<b 
	if(a.sign  == 0 && b.sign ==1)//a负b正 
		return -1;
		
	if(a.sign == 0 && b.sign == 0){			//ab都为负 
		if(a.digit>b.digit)
            return -1;
        else if(a.digit<b.digit)
            return 1;
        else{ //位数一样
            if(strcmp(a.num ,b.num) == 0)		
			return 0;
		else if(strcmp(a.num ,b.num) > 0)
				return -1;	
		else 	return 1;
        }
	}
	
	if(a.sign == 1 && b.sign ==0)		//a正b负
			return 1;
			
	if(a.sign ==1 && b.sign == 1){	
        	//ab都为正 
		if(a.digit>b.digit)
            return 1;
        else if(a.digit<b.digit)
            return -1;
        else{ //位数一样
            if(strcmp(a.num ,b.num) == 0)		
			return 0;
		else if(strcmp(a.num ,b.num) > 0)
				return 1;	
		else 	return -1;
        }
	} 
    return 0;
}

//选择排序
void SelectionSort(BIGINT arr[], int len)
{
        for (int i = 0; i < len; i++)
        {
            BIGINT minValue = arr[i];
            int minIndex = i;
            for (int j = i+1; j < len; j++)
            {
                if (cmp(arr[j],arr[minIndex])<0)
                {
                    minValue = arr[j];
                    minIndex = j;
                }
                
            }
            
            arr[minIndex] = arr[i];
            arr[i] = minValue;

            // PrintArr(arr, len);            
        }
}
//希尔排序
void ShellSort(BIGINT arr[], int len)
{
    for(int gap = len/2; gap >0; gap = gap/2) {
        for (int i = gap; i < len; i++)
        {
            int cur_pos = i;
            BIGINT cur_date = arr[i];
            while(cur_pos-gap >= 0 && cmp(arr[cur_pos-gap],cur_date) >0){ //cur_pos-gap >= 0
                arr[cur_pos] = arr[cur_pos-gap];
                cur_pos = cur_pos - gap;
            }
            arr[cur_pos] = cur_date;
        }
    }
}

//快排
void QuickSort(BIGINT arr[], int begin, int end)
{
    int i = begin, j = end;
    BIGINT curValue = arr[i];
    if( i < j)
    {
        while(i < j) {
            while (i<j && (cmp(curValue ,arr[j] )<= 0)) 
                j--;
            if(i < j)
                arr[i++] = arr[j];
            while(i<j && (cmp(arr[i] ,curValue )<= 0))
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


//归并排序
void MergeSort(BIGINT arr[], int len)
{
    BIGINT* tempMergeArr = (BIGINT*)malloc(sizeof(BIGINT) * len);
    if (tempMergeArr == NULL)
    {
        fprintf(stderr, "malloc error!\n");
        return;
    }
    memset(tempMergeArr, 0, sizeof (BIGINT)*len);

    DivideMergeSort(arr, tempMergeArr, 0, len-1);

    if (tempMergeArr != NULL)
    {
        free(tempMergeArr);
        tempMergeArr = NULL;
    }
}
void DivideMergeSort(BIGINT *arr, BIGINT *tempMergeArr, int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        DivideMergeSort(arr, tempMergeArr, left, middle);
        DivideMergeSort(arr, tempMergeArr, middle + 1, right);
        MergeSortArr(arr, tempMergeArr, left, middle, right);
    }
}
void MergeSortArr(BIGINT *arr, BIGINT *tempArr, int left, int middle, int right)
{
    int i = left;
    int j = middle + 1;
    int tempArrPosition = 0;
    while (i <= middle && j <= right)
    { 
     if(cmp(arr[i],arr[j]) == 1)
      tempArr[tempArrPosition++] = arr[j++] ;
     else if(cmp(arr[i],arr[j]) <= 0)
      tempArr[tempArrPosition++] = arr[i++] ;
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
//辅助函数，求数据的最大位数 
int MaxBit(BIGINT arr[], int arrlen) 
{
    int maxbit = arr[0].digit;              // 最大位数
    for (int i = 1; i < arrlen; i++)
    {
        if (maxbit < arr[i].digit)
            maxbit = arr[i].digit;
    }

    return maxbit;
}

//基数排序
void RadixSort(BIGINT arr[], int len) {
    //先分成负的和别的
    BIGINT* zheng = (BIGINT*)malloc(sizeof(BIGINT) * len);
    BIGINT* fu = (BIGINT*)malloc(sizeof(BIGINT) * len);
    memset(zheng, 0, sizeof (BIGINT)*len);
    memset(fu, 0, sizeof (BIGINT)*len);
    int j=0; //j是正 k是负的下标
    int k=0;
    for(int i = 0; i < len; i++){
        
        if(arr[i].sign==1){
            zheng[j] = arr[i];
            j++;
        }else{
            fu[k] = arr[i];
            k++;
        }
    }

    //再调用子基数排序
     SubRadixSort(zheng,j);
     SubRadixSort(fu,k);

     //排序后打印看看
    // for (int i = 0; i < j; ++i) {
    //     BIGINT tmp_big = zheng[i];
    //     printf("%d %d %s\n",tmp_big.sign,tmp_big.digit,tmp_big.num);
    // }
    //  printf("++++++++++++++++++++++++++++++\n");
    // //打印看看
    // for (int i = 0; i < k; ++i) {
    //     BIGINT tmp_big = fu[i];
    //     printf("%d %d %s\n",tmp_big.sign,tmp_big.digit,tmp_big.num);
    // }
    //最后一步拼接
    for (int i = 0; i < len; ) {
        for (int m = 0; m < k; m++) { //把负的倒放进去
            arr[i] = fu[k-m-1];
            i++;
        }
        for (int m = 0; m < j; m++) { //
            arr[i] = zheng[m];
            i++;
        }
    }

}
//删除多于0 恢复数据
void DeleteZero(BIGINT arr[], int len){
    for(int i = 0; i < len ;i++){
        int j=0;
        for(j = 101-arr[i].digit; j < 101 ;j++){
            arr[i].num[j-101+arr[i].digit ] = arr[i].num[j];
        } 
        arr[i].num[j-101+arr[i].digit] ='\0';
    }
}
//移位补0
void AddZero(BIGINT arr[], int len){
    //将字符串全部放入数据域的最后digit位，前面的空位都补0 
    for(int i = 0; i < len ;i++){
        for(int j = 0; j < arr[i].digit ;j++){
            arr[i].num[101-arr[i].digit + j ] = arr[i].num[j];
        } 
        for(int k = 0; k < 101-arr[i].digit ; k++){
            arr[i].num[k]= '0';
        }
    }
}
void SubRadixSort(BIGINT arr[], int len) {
    
    int bit = MaxBit(arr, len);//获取最大位数
    //移位补0
    AddZero(arr,len);
      //打印看看
    // for (int i = 0; i < len; ++i) {
    //     BIGINT tmp_big = arr[i];
    //     printf("%d %d %s\n",tmp_big.sign,tmp_big.digit,tmp_big.num);
    // }
   // printf("++++++++++++++++++++++++++++++\n");

    //10个桶
    BIGINT **tmp = (BIGINT**)malloc(sizeof(BIGINT*)*10);//用于位数次排序的临时数组tmp[x][0]存储基数为x的数组的元素个数
    memset(tmp, 0, sizeof(BIGINT *)*10);
    for(int i =0; i < 10; i++)
    {
        tmp[i] = (BIGINT*)malloc(sizeof(BIGINT)*(len+1));//len+1是因为每个桶的第一个数据存储该桶的数据个数
        memset(tmp[i], 0, sizeof(BIGINT)*(len+1));
    }
   // printf("1+++++------------------+++++++++++++\n");
    for(int i = 0; i < bit; i++)//位数次排序
    {
        //清空
        for(int k =0; k < 10; k++)
        {
            memset(tmp[k], 0, sizeof(BIGINT)*(len+1));
        }
        //对len个数据进行分桶
        for(int j = 0; j < len; j++) {
            int num = arr[j].num[100-i]-'0';  //判断应该放入哪个桶 
            ++tmp[num][0].digit;//第一个结构体是空的 digit记录桶内元素个数
            tmp[num][tmp[num][0].digit] = arr[j];
        }

        //tmp内容放回数组，进行下一轮基排
        int count = 0; 
        for(int i =0; i < 10; i++)
        {
            for(int j = 1; j <= tmp[i][0].digit; j++)
            {
                arr[count] = tmp[i][j];
                count++;
                // printf("[%d] ", arr[i]);
            }
        }

    }
    //删除多于0 恢复数据
    DeleteZero(arr,len);

   //释放数组内存
    for(int i = 0; i < 10; i++)
    {
        if(tmp[i] != NULL)
        {
            delete(tmp[i]);
            tmp[i] = NULL;

        }
    }
    if(tmp != NULL)
    {
        delete(tmp);
        tmp = NULL;
    }   
}