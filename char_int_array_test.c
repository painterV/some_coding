// Online C compiler to run C program online
#include <stdio.h>
#include <math.h>
#include <string.h>

char a1[]={0x67,0xff};
char a2[]={0x6d,0x72,0x6b,0x6e,0x6e,0x6f,0x73,0x79,0x63,0x63,0xa5};

char a3[]={0x73,0x6b,0x73,0x68,0x6b,0x73,0x73,0x6b,0x79,0x72,0x72,0x6b,0x79,0x6d,0x64,0x79,0x74,0x64,0x74,0x73,0x74,0x6b,0x6b,0x6b,0x74,0x79,0x72,0x68,0x68,0x73,0x79,0x6b,0x73,0x74,0x61,0x68,0x68,0x73,0x73,0x69,0x6f,0x72,0x6b,0x74,0x72,0x72,0x61,0x79,0x79,0x72,0x79,0x79,0x79,0x79,0x6e,0x68,0x72,0x6e,0x74,0x79,0x79,0x72,0x72,0x73,0x74,0x64,0x72,0x68,0x73,0x6b,0x73,0x74,0x6a,0x74,0x63,0x79,0x74,0x6b,0x72,0x68,0x68,0x73,0x72,0x74,0x69,0x72,0x6e,0x6b,0x74,0x6a,0x6b,0x72,0x74,0x73,0x74,0x72,0x79,0x79,0x68,0x6b,0x72,0x79,0x73,0x74,0x73,0x79,0x74,0x6b,0x6b,0x74,0x79,0x68,0x79,0x79,0x79,0x6b,0x79,0x74,0x61,0x61,0x68,0x67,0x80};

//两个整数的加法
int add(int m, int n)
{
    return m + n;
}

//两个整数的比较函数，若相等，则返回0， 若大于则返回1，若小于则返回-1
//参数为int类型
int compare(int p, int q)
{
    if(p == q) {
        return 0;
    } else if(p > q) {
        return 1;
    } else {
        return -1;
    }
}

//函数：求指定整数的平方
int square(int m) {
    return m*m;
}

//函数：获取字符串中可见字符的频率最高的字符
char getFrequentChar(char* a) {
    int count[128] = {0};//使用数组存0-127的char的频次, 默认是0.
    int s = strlen(a);
    for(int i = 0; i < s; i++) {
        if(a[i] < 32 || a[i] > 127) {
            //忽略不可打印的字符:人类不可见读字符
            // printf("ignore: %c\n", a[i]);
            continue;
        }
        // printf("count: %d\n", a[i]);
        count[a[i]] += 1;
    }
    int max = 0; //保存字符的最大频次
    char max_count_ch;//保存频次最高的字符
    for(int i = 0; i < 128; i++) {
        if(max < count[i]) {
            max_count_ch = i;
            max = count[i];
        }
    }
    return max_count_ch;
}

//排序：对表示整型的char数组进行升序排序
// 选择排序法
void sort(char* a) {
    int s = strlen(a);
    //外层循环是排序轮数
    for(int i = 0; i < s; i++) {
        //每一轮排序：找到最小的数的下标，用k来保存
        int k = i;
        for(int j = i; j < s; j++) {
            if(compare(a[j], a[k]) == -1) {
                k = j;
            }
        }
        //然后交换下标是k和i的数
        if(k != i) {
            int temp = a[k];
            a[k] = a[i];
            a[i] = temp;
        }
    }
}

//打印字符数组的函数
void print(char* a) {
    int s = strlen(a);
    for(int i = 0; i < s; i++) {
        printf("%c", a[i]);
    }
    printf("\n");
}

//函数：计算char表示的整型数组里所有数的总和
int getSum(char* a) {
    int res = 0;
    int len = strlen(a);
    //循环遍历数组，依次累加元素
    
    for(int i = 0; i < len; i++) {
        //add函数的参数是int，这里a[i]是char可以直接转为int
        res = add(res, a[i]);
    }
    return res;
}

//合并三个字符串数组为一个字符串数组
char* merge(char* a, char* b, char* c) {
    //首先根据所给的三个字符数组的长度，申请一个新的字符数组内存空间
    //该内存空间大小为 char*类型，长度 是三个字符串的长度之和
    //其中 strlen 是求一个字符数组的长度的函数
    char *strCat = (char*)malloc(strlen(a) + strlen(b) + strlen(c));
    sprintf(strCat,"%s%s%s", a, b, c);
    return strCat;
}
void doLogic(char* a, char* b, char* c) {
    //Step1: 合并三个数组
    char* mix = merge(a, b, c);
    // print(mix);
    int s = strlen(mix);
    
    //Step2: 对数组进行排序
    sort(mix); //按升序排序
    // printf("排序后:\n");
    // print(mix);
    
    int sum = getSum(mix); //计算总和
    float avg = sum * 1.0 / s; //计算平均值
    float median = 0;
    //计算中位数
    if(s % 2 == 0) {
        //如果数组长度是偶数的，则中位数是中间两个数的平均值
        median = (mix[s/2 - 1] + mix[s/2]) * 1.0 / 2;
    } else {
        //如果数组长度是奇数的，则中位数是最中间的数
        //本次输入数据会进入该逻辑分支
        median = mix[s/2];
    }
    printf("总和、平均值、中位数分别是: %d, %.6f, %.6f\n", sum, avg, median);
    
    //计算标准差
    int total = 0;
    for(int i = 0; i < s; i++) {
        //pow是幂函数，这里求标准差首先要求平方和， 底数是 a[i] - avg,  幂指数是2
        total = add(total, pow(a[i]-avg, 2));
    }
    float std = sqrt(total);
    printf("标准差是：%.6f\n", std);
    
    
    // //作为字符串
    char ach = getFrequentChar(mix);
    // printf("字符串是:");
    // print(mix); //打印字符串的函数
    printf("字符串中最频繁的字符是：%c\n", ach);
}
int main()
{
    doLogic(a1, a2, a3);
    return 0;
}
