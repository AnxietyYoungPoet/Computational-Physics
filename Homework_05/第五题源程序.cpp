#include<stdio.h>
#include <time.h>
#include <math.h>
#define Pi 3.14159265359//����Piֵ
#define E 2.718281828459045//����E��ֵ
int f1[5000001];//����ȫ�־�̬���飬��ֹ����������
int f2[5000001];//���������
double x[5000001];
int st[1001];//������������ÿ��С����ĸ���
int n=5000000;//�����С�������������Ŀ
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
    FILE *fp;//�������õ������������dat�ļ�����
    fp=fopen(s,"w");//��ֻд��ʽ����dat�ļ�
    fprintf(fp,"%c",s[0]);//������������浽dat�ļ��У���mathematica��ͼ��������mathematica�﷨
    fprintf(fp,"={");
    for(int i=1;i<1001;i++)
    {
        fprintf(fp,"%lf,",(double)f[i]*100/j);
    }
    fprintf(fp,"%lf}",(double)f[1000]*100/j);//�����ļ���ϣ�ʣ�¹�����mathematica��ȡ�����Լ���ͼ
    fclose(fp);
}
void Schrage16807(int seed,int *f)//��16807���������������
{
    int m=2147483647;
    int a=16807;
    int q=m/a;//q=m/aȡ��
    int r=m%a;//r=m/a������
    int i;
    f[0]=seed;//����ֵ
    for(i=1;i<=n;i++)//��Schrage��������n���������
    {
        if((f[i]=a*(f[i-1]%q)-r*(f[i-1]/q))<0)//�ж��Ƿ����0
            f[i]+=m;//С��0����m
    }//������������
}
int main()
{
    int seed1,seed2,i,j;
    double temp;//������ʱ����x
    int m=2147483647;
    printf("�����������...\n");
    seed1=time(NULL);//��ȡϵͳ��ǰʱ����Ϊ����
    Schrage16807(seed1,f1);//��������0~1�������f1,f2
    printf("��س�\n");
    char c;
    c=getchar();
    seed2=time(NULL);//��ȡϵͳ��ǰʱ����Ϊ����
    Schrage16807(seed2,f2);
    printf("\n����ȡ��������\n");
     for(i=1;i<=n;i++)
    {
        temp=tan((double)f1[i]/m*2*atan(5)-atan(5));
        if((double)f2[i]/m*fx(temp)<px(temp))//������������p[x]�������棬��ȡx
            x[j++]=temp;//j������¼ȡ�ĵ���
    }
    for(i=1;i<j;i++)
    {
        st[(int)floor((100*(x[i]+5)))+1]++;//����x������Ӧ���������+1��100*(x[i]+5)��Χ��0~1000
    }
    printf("�������\n����Ч��Ϊ%lf",(double)(j-1)/n);//(j-1)/nΪʵ�ʳ���Ч��
    output(st,"st.dat",j-1);//��������ļ�
    c=getchar();//�ó�����ͣ�����Զ�����
    return 0;
}
