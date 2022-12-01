#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;

typedef struct Sqlist
{
    int *r;
    int length;
} Sqlist;

Status InitSqlist(Sqlist &L)
{
    L.r = (int *)malloc(MAXSIZE * sizeof(int));
    //分配存储空间
    if (!L.r)
    {
        printf(" 存储分配失败！ ");
        exit(0);
    }             // 存储分配失败
    L.length = 0; // 初始长度为 0
    return OK;
}
Status ScanfSqlist(int &N, Sqlist &L)
{
    int i;
    printf(" 请输入要排序的元素个数N: ");
    scanf("%d", &N);
    for (i = 1; i <= N; i++)
        L.r[i] = rand(); // 随机产生样本整数
    printf("\n\n");
    printf(" 随机产生了%d 个随机数，它们是: \n", N);
    for (i = 1; i <= N; i++)
    {
        printf("%7.2d ", L.r[i]);
    }
    printf("\n");
    L.length = N; // 储存线性表的长度
    return OK;
}

Status PrintfSqlist(int N, Sqlist L)
{
    int i;
    printf(" 数据个数："); // 输出数据个数
    printf("%d\n", L.length);
    printf(" 排序后的数据:(从左向右依次增大)\n"); // 输出数据
    for (i = 1; i <= N; i++)
        printf("%7.2d ", L.r[i]);
    printf("\n");
    return OK;
}

Status InsertSort(Sqlist &L)
{
    int i, j;
    if (L.length == 0)
    {
        printf(" 要排序的数据为空！");
        return ERROR;
    }
    for (i = 2; i <= L.length; i++)
    {
        if (L.r[i] < L.r[i - 1]) //将插入有序子表
        // L.r[i]
        {
            L.r[0] = L.r[i]; //复制为监视哨
            L.r[i] = L.r[i - 1];
            for (j = i - 2; L.r[0] < L.r[j]; j--)
            {
                L.r[j + 1] = L.r[j]; // 记录后移
            }
            L.r[j + 1] = L.r[0]; //插入到正确位置
        }
    }
    return OK;
}

Status BInsertSort(Sqlist &L)
{
    //参考书 P267 算法 10.2
    int i,
        j, mid, low, high;
    if (L.length == 0)
    {
        printf(" 要排序的数据为空！ ");
        return ERROR;
    }
    for (i = 2; i <= L.length; i++)
    {
        L.r[0] = L.r[i]; //将 L.r[i] 暂存在 L.r[0]
        low = 1;
        high = i - 1;
        while (low <= high)
        { // 在 r[low..high] 中折半查找有序插入的位置
            mid = (low + high) / 2;
            if (L.r[0] < L.r[mid])
            { // 插入点在低半区
                high = mid - 1;
            }
            else
            {
                low = mid + 1; // 插入点在高半区
            }
        } // while
        
    }
    
    for (j = i - 1; j >= high + 1; j--)
        {
            //插入点后的数据后移
            L.r[j + 1] = L.r[j];
        }
    return OK;
}

//希尔插入排序
Status ShellInsert(Sqlist &L, int dk)
{
    int i, j;
    //前后位置的增量是 dk
    for (i = dk + 1; i <= L.length; i++) // r[0]只是暂存单元，不是哨兵，
    {
        if (L.r[i] < L.r[i - dk]) //将 L.r[i] 插入有序增量子表
        {
            L.r[0] = L.r[i]; //暂存 L.r[0]
            for (j = i - dk; j > 0 && L.r[0] < L.r[j]; j -= dk)
            {
                L.r[j + dk] = L.r[j]; //记录后移 , 查找插入位置
            }
            L.r[j + dk] = L.r[0]; //插入
        }
    }
    return OK;
}

// 希尔排序
Status
ShellSort(Sqlist &L, int dlta[5], int t)
{
    int i;
    if (L.length == 0)
    {
        printf(" 要排序的数据为空！ ");
        return ERROR;
    }
    for (i = 0; i < t; i++)
    {
        ShellInsert(L, dlta[i]);
    }
    return OK;
}
Status BubbleSort(Sqlist &L)
{
    int i, j, t;
    if (L.length == 0)
    {
        printf(" 要排序的数据为空！ ");
        return ERROR;
    }
    for (i = 1; i <= L.length - 1; i++)
    {
        for (j = 1; j <= L.length - i; j++)
        {
            if (L.r[j] > L.r[j + 1])
            //前面的数据 >后面数据时
            {
                t = L.r[j + 1];
                L.r[j + 1] = L.r[j];
                L.r[j] = t; //将元素交换
            }
        }
    }
    return OK;
}

int Partition(Sqlist &L, int low, int high)
{
    int pivotkey;        //记录关键字
    L.r[0] = L.r[low];   //用子表的第一个纪录作枢轴纪录
    pivotkey = L.r[low]; //用枢轴纪录关键字
    while (low < high)
    {
        while (low < high && L.r[high] >= pivotkey)
        {
            high--;
        }
        L.r[low] = L.r[high];
        // 将比枢轴记录小的记录移到低端
        while (low < high && L.r[low] <= pivotkey)
        {
            low++;
        }
        L.r[high] = L.r[low]; //将比枢轴记录大的数移到高端
    }
    L.r[low] = L.r[0]; // 枢轴记录到位
    return low;
} // Partition 函数
void Qsort(Sqlist &L, int low, int high)
{
    int pivotloc;
    if (low < high) // 长度大于 1，可以进行
    {
        pivotloc = Partition(L, low, high);
        Qsort(L, low, pivotloc - 1);
        // 对低子表递归排序， pivotloc 是枢轴位置
        Qsort(L, pivotloc + 1, high); // 对高子表递归排序
    }
} // Qsort 函数
Status QuickSort(Sqlist &L)
{
    if (L.length == 0)
    {
        printf(" 要排序的数据为空！ ");
        return ERROR;
    }
    Qsort(L, 1, L.length);
    return OK;

} // QuickSort
Status ChooseSort(Sqlist &L)
{
    int i, j, k, t;
    if (L.length == 0)
    {
        printf(" 没有数据！ ");
        return ERROR;
    }
    for (i = 1; i <= L.length; i++)
    // 排序的趟数
    {
        k = i;
        for (j = i + 1; j <= L.length; j++)
        //比较第 i 个元素以及其后的数据中最小的
        {
            if (L.r[j] < L.r[k])
                k = j;
        }
        if (i != j) //将最小数据赋值给 L.r[i]
        {
            t = L.r[i];
            L.r[i] = L.r[k];
            L.r[k] = t;
        }
    }
    return OK;
}

//调整 L.r[s] 的关键字 ,使 L.r[s~m] 成大顶堆
Status HeapAdjust(Sqlist &L, int s, int m)
{
    int i;
    L.r[0] = L.r[s];
    for (i = 2 * s; i + 1 <= m; i *= 2) // 沿数据较大的孩子结点向下筛选
    {
        if (i < m && L.r[i] < L.r[i + 1])
            // i 为数据较大的记录下标
            i++;
        if (L.r[0] >= L.r[i]) // L.r[0] 插入在 S 位置上
            break;
        L.r[s] = L.r[i];
        s = i;
    }
    L.r[s] = L.r[0];
    //插入新数据
    return OK;
}
Status HeapSort(Sqlist &L) // 堆排序
{
    int i, t;
    if (L.length == 0)
    {
        printf(" 没有数据！ ");
        return ERROR;
    }
    for (i = L.length / 2; i > 0; i--)
        HeapAdjust(L, i, L.length);
    for (i = L.length; i > 1; i--)
    {
        t = L.r[1]; //将堆顶记录和当前未经排序的子序列L.r[1..i] 中最后一个记录互换
        L.r[1] = L.r[i];
        L.r[i] = t;
        HeapAdjust(L, 1, i - 1); //将 L.r[1..i-1] 重新调整为大顶堆
    }
    return OK;
}

int main()
{
    Sqlist L;
    Sqlist L0;
    InitSqlist(L); //初始化 L
    InitSqlist(L0);
    int m, i;
    int choice;
    clock_t start, finish; //
    printf("                            算法排序比较系统                               \n");
    printf(" 以下是各个排序算法的代号\n\n");

    printf("1.直接插入排序 \n");
    printf("2.折半插入排序\n");
    printf("3.希尔排序\n");
    printf("4.起泡排序\n");
    printf("5.快速排序\n");
    printf("6.选择排序\n");
    printf("7.堆排序 \n");
    printf("8.退出该系统\n\n");
    ScanfSqlist(m, L0);
    printf("\n");
    printf("1.直接插入排序 \n");
    printf("2.折半插入排序\n");
    printf("3.希尔排序\n");
    printf("4.起泡排序\n");
    printf("5.快速排序\n");
    printf("6.选择排序\n");
    printf("7.堆排序 \n");
    printf("8.退出该系统\n\n");
    printf("\n请选择排序的方式 ,数字 1-7:");
    scanf("%d", &choice);
    //选择排序方式赋值 choice ，用于后面的函数选择
    while (choice < 1 || choice > 8)
    {
        printf(" 输入方式有误。 \n 请输入 1-7 选择排序方式，或者选择 8 退出系统 ");
        scanf("%d", &choice);
    }
    if (choice != 8)
    {
        for (i = 1; i <= L0.length; i++)
            L.r[i] = L0.r[i];
        L.length = L0.length;
    }
    switch (choice)
    {
    case 1: // 直接插入排序
    {
        start = clock();
        InsertSort(L);
        finish = clock();
        break;
    }
    case 2: // 折半插入排序
    {
        start = clock();
        BInsertSort(L);
        finish = clock();
    }
    break;
    case 3: // 起泡排序
    {
        start = clock();
        BubbleSort(L);
        finish = clock();
        break;
    }
    case 4: // 快速排序
    {
        start = clock();
        QuickSort(L);
        finish = clock();
        break;
    }
    case 5: // 选择排序
    {
        start = clock();
        ChooseSort(L);
        finish = clock();
        break;
    }
    case 6: // 堆排序
    {
        start = clock();
        HeapSort(L);
        finish = clock();
        break;
    }
    case 7: // 基数排序
    {
        start = clock();
        // RadixSort(L); //未定义函数先去掉了
        finish = clock();
        break;
    }
    case 8:
        break;
    }
    PrintfSqlist(m, L); //输出数据和 L 的长度
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    //输出算术时间
    printf("\n 本次排序运算所用的时间是： %lf seconds\n", duration);

    return 0;
}
