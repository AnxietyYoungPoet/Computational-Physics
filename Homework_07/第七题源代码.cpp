#include<stdio.h>
#include <time.h>
#include <math.h>
double r[5][5000001];//定义全局静态数组，防止数组过大出错
int N=5000000;//数组大小，即随机数的数目
double fx(double x)//F[x]
{
    return sqrt(x+sqrt(x));
}
double g(double x1,double x2,double x3,double x4,double x5)//g(x)
{
    return (6-x1*x1-x2*x2-x3*x3-x4*x4-x5*x5);
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
void f1()
{
    int seed,m=2147483647,i,j;
    double mean,sum=0;
    seed=time(NULL);//获取时间种子
    printf("当N=%d时，第一个积分10次计算值为：\n",N);
    for(j=1;j<=10;j++)
    {
        sum=0;
        Schrage16807(seed,r[0]);//生成随机数
        for(i=1;i<=N;i++)//计算Monete Carlo 积分值
            {
                sum+=fx(r[0][i]);
            }
        mean=sum/N;//计算Monete Carlo 积分值
        printf("Monte Carlo 积分值为%lf\n",mean);
        seed+=1997;//改变种子值
    }

}
void f2()
{
    int seed,m=2147483647,i,j;
    double mean,sum=0;
    seed=time(NULL);//获取时间种子
    printf("当N=%d时，第二个积分10次计算值为：\n",N);
    for(j=1;j<=10;j++)
    {
        sum=0;
        for(i=0;i<5;i++)//生成5组随机数
        {
            Schrage16807(seed,r[i]);
            seed+=1997;
        }
        for(i=1;i<=N;i++)//计算Monete Carlo 积分值
        {
            sum+=g(r[0][i]*0.7,r[1][i]*0.8,r[2][i]*0.9,r[3][i],r[4][i]*1.1);
        }
        mean=sum/N;
        printf("Monte Carlo 积分值为%lf\n",mean*0.7*0.8*0.9*1.1);
    }

}
int main()
{
    f1();//计算第一个积分
    f2();//计算第二个积分
    char c;
    c=getchar();
    return 0;

}
