#include <stdio.h>
#include <math.h>
#include <time.h>
#define Pi 3.14159265359//定义Pi值
int f1[50001];//定义全局静态数组，防止数组过大出错
int f2[50001];//两组随机数
double x[50001];//用于储存x,y
double y[50001];
int n=50000;//数组大小，即随机数的数目
void output(double *f,char *s)
{
    FILE *fp;//用来将得到的数组输出到dat文件里面
    fp=fopen(s,"w");//以只写方式创建dat文件
    fprintf(fp,"%c",s[0]);//将数组输出储存到dat文件中，用mathematica画图，所以用mathematica语法
    fprintf(fp,"={");
    for(int i=1;i<n;i++)
    {
        fprintf(fp,"%lf,",f[i]);
    }
    fprintf(fp,"%lf}",f[n]);//导出文件完毕，剩下工作由mathematica读取数据以及画图
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
    int seed1,seed2;
    int m=2147483647;
    printf("生成随机数中...\n");
    seed1=time(NULL);//获取系统当前时间作为种子
    Schrage16807(seed1,f1);//生成两组0~1的随机数f1,f2
    printf("请回车\n");
    char c;
    c=getchar();
    seed2=time(NULL);//获取系统当前时间作为种子
    Schrage16807(seed2,f2);
     for(int i=1;i<=n;i++)
    {
        x[i]=sqrt(2*(double)f1[i]/m-((double)f1[i]/m)*((double)f1[i]/m))*cos((double)f2[i]/m*2*Pi);//x=sqrt(2f1-f1^2)cos(2*Pi*f2)
        y[i]=sqrt(2*(double)f1[i]/m-((double)f1[i]/m)*((double)f1[i]/m))*sin((double)f2[i]/m*2*Pi);//y=sqrt(2f1-f1^2)sin(2*Pi*f2)
    }
    output(x,"x.dat");//输出数据
    output(y,"y.dat");
    printf("生成完毕，回车结束程序\n");
    c=getchar();//让程序暂停，不自动结束
    return 0;
}
