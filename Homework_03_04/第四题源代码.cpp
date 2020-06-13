#include <stdio.h>
#include <math.h>
#include <time.h>
#define Pi 3.14159265359//����Piֵ
int f1[50001];//����ȫ�־�̬���飬��ֹ����������
int f2[50001];//���������
double x[50001];//���ڴ���x,y
double y[50001];
int n=50000;//�����С�������������Ŀ
void output(double *f,char *s)
{
    FILE *fp;//�������õ������������dat�ļ�����
    fp=fopen(s,"w");//��ֻд��ʽ����dat�ļ�
    fprintf(fp,"%c",s[0]);//������������浽dat�ļ��У���mathematica��ͼ��������mathematica�﷨
    fprintf(fp,"={");
    for(int i=1;i<n;i++)
    {
        fprintf(fp,"%lf,",f[i]);
    }
    fprintf(fp,"%lf}",f[n]);//�����ļ���ϣ�ʣ�¹�����mathematica��ȡ�����Լ���ͼ
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
    int seed1,seed2;
    int m=2147483647;
    printf("�����������...\n");
    seed1=time(NULL);//��ȡϵͳ��ǰʱ����Ϊ����
    Schrage16807(seed1,f1);//��������0~1�������f1,f2
    printf("��س�\n");
    char c;
    c=getchar();
    seed2=time(NULL);//��ȡϵͳ��ǰʱ����Ϊ����
    Schrage16807(seed2,f2);
     for(int i=1;i<=n;i++)
    {
        x[i]=sqrt(2*(double)f1[i]/m-((double)f1[i]/m)*((double)f1[i]/m))*cos((double)f2[i]/m*2*Pi);//x=sqrt(2f1-f1^2)cos(2*Pi*f2)
        y[i]=sqrt(2*(double)f1[i]/m-((double)f1[i]/m)*((double)f1[i]/m))*sin((double)f2[i]/m*2*Pi);//y=sqrt(2f1-f1^2)sin(2*Pi*f2)
    }
    output(x,"x.dat");//�������
    output(y,"y.dat");
    printf("������ϣ��س���������\n");
    c=getchar();//�ó�����ͣ�����Զ�����
    return 0;
}
