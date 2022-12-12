// Online C compiler to run C program online
#include <stdio.h>
char a1[]={0x67,0xff};
char a2[]={0x6d,0x72,0x6b,0x6e,0x6e,0x6f,0x73,0x79,0x63,0x63,0xa5};

char a3[]={0x73,0x6b,0x73,0x68,0x6b,0x73,0x73,0x6b,0x79,0x72,0x72,0x6b,0x79,0x6d,0x64,0x79,0x74,0x64,0x74,0x73,0x74,0x6b,0x6b,0x6b,0x74,0x79,0x72,0x68,0x68,0x73,0x79,0x6b,0x73,0x74,0x61,0x68,0x68,0x73,0x73,0x69,0x6f,0x72,0x6b,0x74,0x72,0x72,0x61,0x79,0x79,0x72,0x79,0x79,0x79,0x79,0x6e,0x68,0x72,0x6e,0x74,0x79,0x79,0x72,0x72,0x73,0x74,0x64,0x72,0x68,0x73,0x6b,0x73,0x74,0x6a,0x74,0x63,0x79,0x74,0x6b,0x72,0x68,0x68,0x73,0x72,0x74,0x69,0x72,0x6e,0x6b,0x74,0x6a,0x6b,0x72,0x74,0x73,0x74,0x72,0x79,0x79,0x68,0x6b,0x72,0x79,0x73,0x74,0x73,0x79,0x74,0x6b,0x6b,0x74,0x79,0x68,0x79,0x79,0x79,0x6b,0x79,0x74,0x61,0x61,0x68,0x67,0x80};
//编写两个整数加法的函数
//要考虑加法之后的数字大小(只能用 0 至 127 的数字)
//这里入参类型是 int
int add(int m, int n)
{
    return m + n;
}

//两个整数的比较函数，若相等，则返回0， 若大于则返回1，若小于则返回-1
//参数为int类型
int compare(int p, int q)
{
    //指针变量前加*是取存储在该地址的内容
    if(p == q) {
        return 0;
    } else if(p > q) {
        return 1;
    } else {
        return -1;
    }
}

//求三个整数的中位数
int getMedian(int m, int n, int l) {
    
    //首先如果三个里面有任意两个数相等，那么必然中位数是其中一个，直接返回即可
    if(m = n || m == l) {
        return m;
    }
    //同上
    if(n = l) {
        return n;
    }
    //排除掉 有相同的数的情况后
    //假设 m是中位数，那么 一定有 n < m < l 或者 l < m < n
    //那么不管m作为compare的第一个参数，还是第二个参数: 一定会有 compare(m, l) + compare(m, n) == 0
    // or compare(l, m) + compare(n, m) == 0
    // 因此我们使用如下的条件来判断哪个是中位数
    if(add(compare(n, m), compare(l, m)) == 0) {
        return m;
    }
    if(add(compare(l, n), compare(m, n)) == 0) {
        return n;
    }
    if(add(compare(m, l), compare(n, l)) == 0) {
        return l;
    }
}

//函数：求指定整数的平方
int square(int m) {
    return m*m;
}

char getFrequentChar(char* a) {
    int count[128] = {0};//使用数组存0-127的char的频次, 默认是0.
    int s = sizeof(a)/sizeof(char); //计算字符数组（也是字符串）的长度
    for(int i = 0; i < s; i++) {
        if(*(a+i) < 32 || *(a+i) > 127) {
            //忽略不可打印的字符
            continue;
        }
        count[*(a+i)] += 1;
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

void print(char* a) {
    int s = sizeof(a)/sizeof(char);
    for(int i = 0; i < s; i++) {
        if(*(a+i) < 32 || *(a+i) > 127) {
            //忽略不可打印的字符
            continue;
        }
        printf("%c", a[i]);
    }
    printf("\n");
}
void doLogic(char* a, char* b, char* c) {
    //视为char表示的整型数据
    int m = *a; //将char指针转为int类型
    int n = *b;//同上
    int l = *c;//同上
    
    int sum = add(m, add(n, l)); // add(n, l)先求n和l的和, 再和 m求和
    float avg = sum * 1.0 / 3; //求平均数
    int median = getMedian(m, n, l); //调用求中位数函数
    
    //打印结果
    printf("三个数分别是：%d, %d, %d\n", m, n, l);
    printf("三个数的总和、平均值、中位数分别是: %d, %.6f, %d\n", sum, avg, median);
    
    //计算标准差 sqrt((m-avg)^2 + (n-avg)^2 + (l-avg)^2)
    int total = add(add(square(m-avg), square(n-avg)), square(l-avg));
    float std = sqrt(total);
    
    printf("三个数的标准差是：%f\n", std);
    
    //求最频繁的字符
    char ach = getFrequentChar(a);
    char bch = getFrequentChar(b);
    char cch = getFrequentChar(c);
    
    printf("第一个字符串是:");
    print(a); //打印字符串的函数
    printf("第一个字符串中最频繁的字符是：%c\n", ach);
    
    printf("第二个字符串是:");
    print(b);
    printf("第二个字符串中最频繁的字符是：%c\n", bch);
    
    printf("第三个字符串是:");
    print(c);
    printf("第三个字符串中最频繁的字符是：%c\n", cch);
}

int main()
{
    doLogic(a1, a2, a3);
	return 0; 
	
	
}
