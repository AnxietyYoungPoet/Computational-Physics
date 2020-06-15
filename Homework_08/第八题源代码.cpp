#include<stdio.h>
#include <time.h>
#include <math.h>
#define Pi 3.1415926535897932385
double r[1000001];//定义全局静态数组，防止数组过大出错
double st[100000];//储存y[N2]
int N=1000000;//数组大小，即随机数的数目
int N2=100000;//各种分布下每种N都抽样10W次
void output(double *f,char *s)
{
    FILE *fp;//用来将得到的数组输出到dat文件里面
    fp=fopen(s,"w");//以只写方式创建dat文件
    fprintf(fp,"%c",s[0]);//将数组输出储存到dat文件中，用mathematica画图，所以用mathematica语法
    fprintf(fp,"={");
    for(int i=1;i<100000;i++)
    {
        fprintf(fp,"%lf,",f[i]);
    }
    fprintf(fp,"%lf}",f[100000]);//导出文件完毕，剩下工作由mathematica读取数据以及画图
    fclose(fp);
}
void Schrage16807(int seed,double *f)//用16807产生器产生随机数
{
    int m=2147483647;
    int a=16807;
    int q=m/a;//q=m/a取整
    int r=m%a;//r=m/a的余数
    int i;
    f[0]=seed;//种子值
    for(i=1;i<=N;i++)//用Schrage方法产生n个随机数，
    {
        if((f[i]=a*((int)f[i-1]%q)-r*((int)f[i-1]/q))<0)//判断是否大于0
            f[i]+=m;//小于0加上m
    }//产生随机数完毕
    for(i=1;i<=N;i++)
    {
        f[i]/=m;
    }
}
double Mean(int star,int d)//计算N个（从第star个开始，到stard+N-1个）值的平均
{
    int i;
    double sum=0;
    for(i=star;i<star+d;i++)
    {
        sum+=r[i];
    }
    return sum/d;
}
void EXP()
{
    int m=2147483647,seed,i;
    seed=time(NULL);
    Schrage16807(seed,r);//生成随机数
    for(i=1;i<=N;i++)
    {
        r[i]=log(1/r[i]);//x=ln(1/r)
    }
}
void LIN()
{
    int m=2147483647,seed,i;
    seed=time(NULL);
    Schrage16807(seed,r);//生成随机数
    for(i=1;i<=N;i++)
    {
        r[i]=sqrt(r[i]);//x=sqrt(r)
    }
}
void SIN()
{
    int m=2147483647,seed,i;
    seed=time(NULL);
    Schrage16807(seed,r);//生成随机数
    for(i=1;i<=N;i++)
    {
        r[i]=sin(Pi*(r[i]-0.5));//x=sin(Pi*(r-0.5))
    }
}
void CLT(int NN,double u ,double sigma)
{
    int i;
    double mean;
    for(i=1;i<=N2;i++)
    {
        mean=Mean(2*i-1,NN);
        st[i]=(mean-u)*sqrt(NN)/sigma;//计算y=（<x>-u)/u/sigma
    }
}
int main()
{
    printf("指数分布：\n");
    EXP();//指数分布u=1,sigma=1
    CLT(2,1,1);//当N=2时计算分布
    output(st,"exp1.dat");//输出结果
    CLT(5,1,1);//当N=5时计算分布
    output(st,"exp2.dat");
    CLT(10,1,1);//当N=10时计算分布
    output(st,"exp3.dat");
    printf("已经输出完毕\n");
    printf("余弦分布:\n");
    SIN();//余弦分布，u=0,sigma=sqrt(0.5)
    CLT(2,0,sqrt(0.5));
    output(st,"sin1.dat");
    CLT(5,0,sqrt(0.5));
    output(st,"sin2.dat");
    CLT(10,0,sqrt(0.5));
    output(st,"sin3.dat");
    printf("已经输出完毕\n");
    printf("线性分布:\n");
    LIN();//线性分布，u=2/3,sigma=sqrt(1/18)
    CLT(2,(double)2/3,sqrt((double)1/18));
    output(st,"lin1.dat");
    CLT(5,(double)2/3,sqrt((double)1/18));
    output(st,"lin2.dat");
    CLT(10,(double)2/3,sqrt((double)1/18));
    output(st,"lin3.dat");
    printf("已经输出完毕\n回车结束程序");

    char c;
    c=getchar();
    return 0;

}
