#include<stdio.h>
#include <math.h>
int f[50001];//定义全局静态数组，防止数组过大出错，第一个用来储存种子值，不做为随机数
int n=50000;//数组大小，即随机数的数目
void output(char *s,int m)
{
    FILE *fp;//用来将得到的数组输出到dat文件里面
    fp=fopen(s,"w");//以只写方式创建dat文件
    fprintf(fp,"f={");//将数组输出储存到dat文件中，用mathematica画图，所以用mathematica语法
    for(int i=1;i<n;i++)
    {
        fprintf(fp,"%lf,",(double)f[i]/m);//这里只存n个随机数，而不是{f[i],f[i+1]}数据点，是为了压缩文件大小
    }
    fprintf(fp,"%lf}",(double)f[n]/m);//导出文件完毕，剩下工作由mathematica读取数据以及画图
    fclose(fp);
}
int main()
{
    int m=2147483647;
    int a=16807;
    int q=m/a;//q=m/a取整
    int r=m%a;//r=m/a的余数
    int i,seed;//seed用于储存种子值
    printf("由16807产生器产生50000个随机数\n");
    printf("请输入种子值(0~%d)\n",m-1);
    scanf("%d",&seed);//由用户键入种子值
    f[0]=seed;//种子值
    for(i=1;i<=n;i++)//用Schrage方法产生n个随机数，
    {
        if((a*(f[i-1]%q)-r*(f[i-1]/q))>0)//判断是否大于0
        {
            f[i]=a*(f[i-1]%q)-r*(f[i-1]/q);//大于0情况
        }
        else
            f[i]=a*(f[i-1]%q)-r*(f[i-1]/q)+m;//小于0情况
    }//产生随机数完毕
    output("Schrage.dat",m);//将数据输出到文件中
    printf("输出完毕\n(回车退出程序)");
    char c;
    while((c=getchar())!='\n'&&c!=EOF);//清空缓冲区
    c=getchar();//让程序暂停，不自动结束
    return 0;
}
