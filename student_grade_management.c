/*
**
**学生成绩管理系统作业代码
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 0;

struct student
{
    char name[50];  //姓名
    char gender;    //性别
    int Clanguage;  // C语言
    int math;       //数学
    int english;    //英语
    int sum;        //总分
    double average; //平均分
    int min;        //最低分
    int max;        //最高分
} a[30];


int i = 0;
void start();
void shuru();
void sum_average();
void max_min();
void biaoge();
int find();

void start()
{
    printf("********************学生成绩管理系统**********************\n");
    printf("**********************************************************\n");
    printf("                        功能列表                        \n");
    printf("**********************************************************\n");
    printf("                    1--输入成绩\n");
    printf("                    2--求总分和平均值\n");
    printf("                    3--求最高分和最低分\n");
    printf("                    4--输出表格\n");
    printf("                    5--成绩查询\n");
    printf("                    0--退出系统\n");
    printf("**********************************************************\n");
}

void shuru() //输入信息
{
    int i;
    printf("请输入学生总数:\n");
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        printf("请输入第%d个同学的信息\n", i + 1);
        printf("输入姓名:\n");
        scanf("%s", &a[i].name);
        getchar();
        printf("输入三科成绩\n");

        printf("输入C语言成绩:");
        scanf("%d", &a[i].Clanguage);
        printf("\nC语言成绩是:%d分\n", a[i].Clanguage);

        printf("\n输入数学成绩:");
        scanf("%d", &a[i].math);
        printf("\n数学成绩是:%d\n分", a[i].math);

        printf("输入英语成绩:");
        scanf("%d", &a[i].english);
        printf("\n英语成绩是:%d分\n", a[i].english);
    }
}

void sum_average() //求总分和平均分
{
    for(int i = 0; i < N; i++) {
        a[i].sum = a[i].Clanguage + a[i].math + a[i].english;
        a[i].average = (a[i].Clanguage + a[i].math + a[i].english) * 1.0 / 3;        
    }
    printf("完成总分和平均分计算\n");
}

void max_min() //求最高分和最低分
{
    for(int i = 0; i < N; ++i) {
        int max = 0;
        int min = 100;
        
        if(max < a[i].Clanguage) {
            max = a[i].Clanguage;
        }
        if(max < a[i].math) {
            max = a[i].math;
        }
        if(max < a[i].english) {
            max = a[i].english;
        }
        if(min > a[i].Clanguage) {
            min = a[i].Clanguage;
        }
        if(min > a[i].math) {
            min = a[i].math;
        }
        if(min > a[i].english) {
            min = a[i].english;
        }
        
        a[i].max = max;
        a[i].min = min;
    }
    printf("完成最高分和最低分计算\n");
}

void biaoge() //输出表格
{
    printf("姓名\tC language\t数学\t英语\t最高分\t最低分\t总分\t平均分\n");
    for (i = 0; i < N; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%lf\n", a[i].name, a[i].Clanguage, a[i].math, a[i].english, a[i].max, a[i].min, a[i].sum, a[i].average);
    }
}

int find() //查询
{
    //输入所查姓名，查询成绩
    char b[40];
    printf("输入你要查询的姓名:");
    scanf("%s", &b);
    int findFlag = 0;
    for (i = 0; i < N; i++)
    {
        //寻找所查成绩
        if (strcmp(a[i].name, b) == 0)
        {
            printf("姓名\tC language\t数学\t英语\t最高分\t最低分\t总分\t平均分\n");
            findFlag = 1;
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%lf\n", a[i].name, a[i].Clanguage, a[i].math, a[i].english, a[i].max, a[i].min, a[i].sum, a[i].average);
            break;
        }
    }
    if(findFlag == 0) {
        printf("查无此人，请重新查询\n");
    }
}

int main()
{

    int choice = 0;
    do
    {
        start(); //欢迎
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            shuru();
            break;
        case 2:
            sum_average();
            break;
        case 3:
            max_min();
            break;
        case 4:
            biaoge();
            break;
        case 5:
            find();
            break;
        case 0:
            break;
        default:
            printf("功能选择错误，请重新输入选择:\n");
            break;
        }
    } while (choice != 0);
    printf("结束\n");
    return 0;
} //主函数
