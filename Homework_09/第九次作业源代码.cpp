#include<stdio.h>
#include <time.h>
#include <math.h>
#define Pi 3.14159265358
double r[20000001];//定义全局静态数组，防止数组过大出错
double cov[1001];//储存y[N2]
int N=20000000;//数组大小，即随机数的数目
void output(double *f,char *s)
{
    FILE *fp;//用来将得到的数组输出到dat文件里面
    fp=fopen(s,"w");//以只写方式创建dat文件
    fprintf(fp,"%c",s[0]);//将数组输出储存到dat文件中，用mathematica画图，所以用mathematica语法
    fprintf(fp,"={0.5,");
    for(int i=1;i<1000;i++)
    {
        fprintf(fp,"%lf,",f[i]/20000);
    }
    fprintf(fp,"%lf}",f[1000]/20000);//导出文件完毕，剩下工作由mathematica读取数据以及画图
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
void Cov()
{
    int i,j,k,seed,a0,n=1,da=0;
    seed=time(NULL);//获取当前时间作为种子
    Schrage16807(seed,r);//产生N个随机数
    for(j=1;j<=20000;j++)//20000为做系综平均的数目
    {
        a0=(int)floor(361*r[j]);//初始取向
        da=0;//初始化角位移
        for(k=1;k<=1000;k++)//分别计算t从0到1000的cov(t)
            {
                if(r[n]<=0.5)//角位移，每次变化5度
                    da-=5;
                else da+=5;
                n++;//获取下一个随机数
                cov[k]+=cos((double)a0/360*2*Pi)*cos((double)(a0+da)/360*2*Pi);//计算一个cov
            }
    }
}
int main()
{
    printf("正在用Monte Carlo方法计算cov(t)\n");
    Cov();//计算自关联函数
    printf("计算完毕，正在输出数据\n");
    output(cov,"cov.dat");//输出数据
    printf("输出完毕，回车结束程序\n");
    char c;
    c=getchar();
    return 0;

}
