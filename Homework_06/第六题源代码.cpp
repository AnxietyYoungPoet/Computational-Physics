#include<stdio.h>
#include <time.h>
#include <math.h>
double data[][2]={{2900,1158},{2901,1163},{2902,1167},{2903,1171},{2904,1178},{2905,1188},{2906,1200},
{2907,1214},{2908,1233},{2909,1256},{2910,1281},{2911,1303},{2912,1320},{2913,1335},{2914,1351},
{2915,1368},{2916,1386},{2917,1402},{2918,1417},{2919,1432},{2920,1449},{2921,1469},{2922,1490},
{2923,1511},{2924,1531},{2925,1551},{2926,1572},{2927,1597},{2928,1623},{2929,1647},{2930,1666},
{2931,1684},{2932,1704},{2933,1728},{2934,1753},{2935,1778},{2936,1800},{2937,1819},{2938,1838},
{2939,1856},{2940,1873},{2941,1888},{2942,1901},{2943,1915},{2944,1937},{2945,1969},{2946,2006},
{2947,2045},{2948,2081},{2949,2118},{2950,2158},{2951,2207},{2952,2265},{2953,2329},{2954,2389},
{2955,2437},{2956,2472},{2957,2501},{2958,2532},{2959,2569},{2960,2612},{2961,2656},{2962,2692},
{2963,2713},{2964,2712},{2965,2687},{2966,2641},{2967,2575},{2968,2496},{2969,2409},{2970,2328},
{2971,2263},{2972,2218},{2973,2185},{2974,2149},{2975,2096},{2976,2021},{2977,1930},{2978,1838},
{2979,1762},{2980,1715},{2981,1696},{2982,1697},{2983,1701},{2984,1692},{2985,1659},{2986,1601},
{2987,1525},{2988,1442},{2989,1358},{2990,1277},{2991,1206},{2992,1194},{2993,1458},{2994,2664},
{2995,6190},{2996,13605},{2997,24698},{2998,35560},{2999,40123},{3000,35340},{3001,24264},{3002,12980},
{3003,5409},{3004,1755},{3005,443},{3006,87},{3007,13},{3008,2},{3009,0},{3010,0}};
int r1[1000001];//定义全局静态数组，防止数组过大出错
int r2[1000001];
int cy[112];//储存直接抽样的频数
int sx[111];//储存舍取方法的频数
int count=0;//舍取方法中舍取点的计数
int n=1000000;//数组大小，即随机数的数目
void output(int *f,char *s,int N,int sum)
{
    FILE *fp;//用来将得到的数组输出到dat文件里面
    fp=fopen(s,"w");//以只写方式创建dat文件
    fprintf(fp,"%c",s[0]);//将数组输出储存到dat文件中，用mathematica画图，所以用mathematica语法
    fprintf(fp,"={");
    for(int i=1;i<N;i++)
    {
        fprintf(fp,"%lf,",(double)f[i]/sum);
    }
    fprintf(fp,"%lf}",(double)f[N]/sum);//导出文件完毕，剩下工作由mathematica读取数据以及画图
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
void shexuan()
{
    int seed1,seed2,sum=0,i,j;
    int m=2147483647;
    for(i=1;i<=111;i++)//将所给的数据做频率归一化
    {
        sum+=data[i-1][1];
    }
    for(i=1;i<=111;i++)
        data[i-1][1]/=sum;
    printf("生成随机数中...\n");
    seed1=time(NULL);//获取系统当前时间作为种子
    Schrage16807(seed1,r1);//生成0~1的随机数组r1
    char c;
    printf("请回车\n");
    c=getchar();
    seed2=time(NULL);
    Schrage16807(seed2,r2);//生成0~1的随机数组r2
    for(i=1;i<=n;i++)
    {
        if((double)r1[i]/m<=0.009*94/2.606)//当r1小于0.009*94/2.606
        {
            j=(int)floor((double)r1[i]/m*2.606/0.009);//根据对应r1的大小，确定xn
            if(0.009*r2[i]/m<=data[j+1][1])//判断r2*F[x]是否小于Pn
                {
                    sx[j+1]++;//是则对应区间计数加一
                    count++;//实际取的点数加一
                }
        }
        else//当r1大于0.009*94/2.606
        {
            j=(int)floor(((double)r1[i]/m*2.606-0.846)/0.11)+94;//根据对应r1的大小，确定xn
            if(0.11*r2[i]/m<=data[j+1][1])//判断r2*F[x]是否小于Pn
                {
                    sx[j+1]++;//是则对应区间计数加一
                    count++;//实际取的点数加一
                }
        }
    }
    printf("舍选法抽样效率为%lf\n",(double)count/n);
    output(sx,"sx.dat",110,count);
}
void chouyang()
{
     int seed,i,j;
     int m=2147483647;
     double sum=0;
     for(i=1;i<=111;i++)//得到P[x]的累积函数
     {
         sum+=data[i-1][1];
         data[i-1][1]=sum;
     }
     seed=time(NULL);
     Schrage16807(seed,r1);
     for(i=1;i<=n;i++)
     {
         for(j=1;j<=111;j++)
         {
             if((double)r1[i]/m<=data[j-1][1])//当Pn-1<r1<Pn时，对应的区间计数加一
             {
                 cy[j]++;
                 break;
             }
         }
     }
     output(cy,"cy.dat",111,n);
}
int main()
{
    shexuan();//舍取法抽样
    chouyang();//直接抽样
    return 0;
}

