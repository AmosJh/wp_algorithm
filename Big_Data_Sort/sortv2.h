
typedef struct bigint{
	char num[102];	//大整数数据域 最后一个是\0
	int sign;	//大整数符号位 
	int digit;	//大整数位数  //最多101位
}BIGINT;

int cmp(BIGINT a , BIGINT b);

void SelectionSort(BIGINT arr[], int len);

void ShellSort(BIGINT arr[], int len);

void QuickSort(BIGINT arr[], int begin, int end);

void MergeSort(BIGINT arr[], int len);

void DivideMergeSort(BIGINT *arr, BIGINT *tempMergeArr, int left, int right);

void MergeSortArr(BIGINT *arr, BIGINT *tempArr, int left, int middle, int right);

void RadixSort(BIGINT arr[], int len);

void SubRadixSort(BIGINT arr[], int len);

int MaxBit(BIGINT arr[], int arrlen) ;

void DeleteZero(BIGINT arr[], int len);

void AddZero(BIGINT arr[], int len);