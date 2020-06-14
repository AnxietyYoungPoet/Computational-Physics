#include<stdio.h>
#include <time.h>
#include <math.h>
#define Pi 3.14159265359//定义Pi值
#define E 2.718281828459045//定义E的值
int f1[5000001];//定义全局静态数组，防止数组过大出错
int f2[5000001];//两组随机数
double x[5000001];
int st[1001];//用来储存落入每个小区间的个数
int n=5000000;//数组大小，即随机数的数目
double fx(double x)//F[x]
{
    return 1.6/(Pi*(1+x*x));
}
double px(double x)//p[x]
{
    return pow(E,-x*x/2)/sqrt(2*Pi);
}
void output(int *f,char *s,int j)
{
    FILE *fp;//用来将得到的数组输出到dat文件里面
    fp=fopen(s,"w");//以只写方式创建dat文件
    fprintf(fp,"%c",s[0]);//将数组输出储存到dat文件中，用mathematica画图，所以用mathematica语法
    fprintf(fp,"={");
    for(int i=1;i<1001;i++)
    {
        fprintf(fp,"%lf,",(double)f[i]*100/j);
    }
    fprintf(fp,"%lf}",(double)f[1000]*100/j);//导出文件完毕，剩下工作由mathematica读取数据以及画图
    fclose(fp);
}
void Schrage16807(int seed,int *f)//用16807产生器产生随机数
{
    int m=2147483647;
    int a=16807;
    int q=m/a;//q=m/a取整
    int r=m%a;//r=m/a的余数
    int i;
    f[0]=seed;//种子值
    for(i=1;i<=n;i++)//用Schrage方法产生n个随机数，
    {
        if((f[i]=a*(f[i-1]%q)-r*(f[i-1]/q))<0)//判断是否大于0
            f[i]+=m;//小于0加上m
    }//产生随机数完毕
}
int main()
{
    int seed1,seed2,i,j;
    double temp;//用于临时储存x
    int m=2147483647;
    printf("生成随机数中...\n");
    seed1=time(NULL);//获取系统当前时间作为种子
    Schrage16807(seed1,f1);//生成两组0~1的随机数f1,f2
    printf("请回车\n");
    char c;
    c=getchar();
    seed2=time(NULL);//获取系统当前时间作为种子
    Schrage16807(seed2,f2);
    printf("\n用舍取法抽样中\n");
     for(i=1;i<=n;i++)
    {
        temp=tan((double)f1[i]/m*2*atan(5)-atan(5));
        if((double)f2[i]/m*fx(temp)<px(temp))//如果随机点落在p[x]曲线下面，则取x
            x[j++]=temp;//j用来记录取的点数
    }
    for(i=1;i<j;i++)
    {
        st[(int)floor((100*(x[i]+5)))+1]++;//遍历x，将对应的区间计数+1，100*(x[i]+5)范围在0~1000
    }
    printf("生成完毕\n抽样效率为%lf",(double)(j-1)/n);//(j-1)/n为实际抽样效率
    output(st,"st.dat",j-1);//输出数据文件
    c=getchar();//让程序暂停，不自动结束
    return 0;
}
