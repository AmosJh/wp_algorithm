大作业(排序算法)要求：
对所有算法(选择排序，归并排序，快速排序，希尔排序，基数排序)进行分析并实现，分析其在不同规模的输入下单机性能变化情况；同时实现对于以下两种输入的排序:
1、对数值的范围在的数组排序，此项任务只能使用C或C++完成。
2、利用多线程实现大规模数据的分布式排序，输入超过100万为最低大规模要求。

注意问题：
1、数据量目前最大量级为1e6，1e7会出现栈溢出。还未改用堆内存存储数据
2、文件量很少，未使用makefile。简单使用shell编译即可
3、大数据量验证的时候可使用./SortMain >> log 重定向数据查看数据打印，并使用EXCEL排序比对。(需要手动的打开代码中的printf打印)


