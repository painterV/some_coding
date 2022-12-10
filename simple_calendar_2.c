#include <stdio.h>
#include <time.h>
// 判断是否为闰年函数
int isLeapYear(int);
// 判断某年某月的第一天是周几的函数
int daysWeek(int, int);
// 判断月份有几天函数
int monthDays(int, int);
// 输出某年某月日历函数
void monthCalendar(int, int);
int main()
{
    int Year, Month;
    // 模式选择
    int mode;
    printf("-----------------------------------------\n");
    printf("|               简易日历                |\n");
    printf("-----------------------------------------\n");
    printf("|     (0) 退出系统                      |\n");
    printf("-----------------------------------------\n");
    printf("|     (1) 输入年份打印出全年历          |\n");
    printf("-----------------------------------------\n");
    printf("|     (2) 输入年份月份打印出月日历      |\n");
    printf("-----------------------------------------\n");
    printf("|     (3) 打印出当前月的日历            |\n");
    // printf("-----------------------------------------\n");
    // printf("|     (4) 打印出当前月的日历            |\n");
    printf("-----------------------------------------\n");
    printf("|    请输入数字1 2 3以选择要使用的功能  |\n");
    printf("-----------------------------------------\n");
    int flag = 1;
    while(flag) {
        printf("输入数字：");
        scanf("%d", &mode);
        printf("\n");
        if (mode == 1)
        {
            // 实现第一个功能
            printf("请输入年份： ");
            scanf("%d", &Year);
            // 从1遍历到12月 代表1月到十二月
            for (int i = 1; i <= 12; i++)
            {
                printf("--------------------------------------------------\n");
                printf("%d 年 %d 月\n", Year, i);
                monthCalendar(Year, i);
            }
        }
        else if (mode == 2)
        {
            // 实现第二个功能
            printf("请输入年份： ");
            scanf("%d", &Year);
            printf("请输入月份： ");
            scanf("%d", &Month);
            monthCalendar(Year, Month);
        }
        else if (mode == 3)
        {
            // 固定格式
            time_t timep;
            struct tm *p;
            time(&timep);
            p = gmtime(&timep);
            //获取当前年份,从1900开始，所以要加1900
            Year = 1900 + p->tm_year;
            //获取当前月份,范围是0-11,所以要加1
            Month = 1 + p->tm_mon;
            printf("当前时间为:%d年%d月\n", Year, Month);
            printf("--------------------------------------------------\n");
            printf("%d 年 %d 月\n", Year, Month);
            monthCalendar(Year, Month);
        } else if(mode == 0) {
            //退出
            printf("退出系统");
            break;
        }
        else
        {
            printf("请输入数字1 2 3选择功能 输入其他字符无效！");
        }
    }
 
    return 0;
}
// 判断是否为闰年
int isLeapYear(int Year)
{
    // 如果能整除4且不能整除100或能整除400，则为闰年
    if (Year % 4 == 0 && Year % 100 != 0 || Year % 400 == 0)
    {
        return 1;
    }
    return 0;
}
// 判断月份有几天
int monthDays(int Year, int Month)
{
    // 如果月份为1、3、5、7、8、10、12 天数为31天
    if (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12)
    {
        return 31;
    }
    // 如果月份为4、6、9、11 天数为30天
    else if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
    {
        return 30;
    }
    else
    {
        // 月份为2月 如果是闰年 天数为29天
        if (isLeapYear(Year))
        {
            return 29;
        }
        // 如果不是闰年 天数为28天
        return 28;
    }
}
// 判断某年某月的第一天是周几
int daysWeek(int Year, int Month)
{
    // day用于记录总天数
    // day1记录每月的天数，结合下面代码理解
    int day = 0, day1 = 0;
    // 得到从1900年到某年的天数
    /**
     * @brief
     * 由于1900年1月1日为周一 得到1900年到某年的天数之后
     * 只需要用天数取7的余数，余数即是某年1月1日的周几
     * 所以也可以换为其他1月1日为周一的年份，使用1900年
     * 后，只能判断出1900年之后的年份
     */
    for (int i = 1900; i < Year; i++)
    {
        // 判断闰年
        if (isLeapYear(i))
        {
            day = day + 366;
        }
        else
        {
            day = day + 365;
        }
    }
    //判断月份
    for (int m = 1; m <= Month; m++)
    {
        day1 = monthDays(Year, m);
        if (m < Month)
        {
            // 计算天数
            day = day + day1;
        }
    }
    // week为某年某月第一天的周几
    int week = day % 7;
    return week;
}
// 具体实现打印某年某月日历
void monthCalendar(int Year, int Month)
{
    printf("--------------------------------------------------\n");
    printf("一\t二\t三\t四\t五\t六\t日\n");
    //判断这个月的第一天是星期几
    int t = daysWeek(Year, Month);
    // 判断月份有几天
    int day1 = monthDays(Year, Month);
    for (int i = 0; i < t; i++)
    {
        printf("\t");
    }
    //控制输出格式
    for (int i = 1; i <= day1; i++)
    {
        printf("%d\t", i);
        if ((i + t) % 7 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
    printf("--------------------------------------------------\n");
    printf("\n");
}
