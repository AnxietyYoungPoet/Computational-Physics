#include<stdio.h>
#include <math.h>
int f[50001];//����ȫ�־�̬���飬��ֹ������������һ��������������ֵ������Ϊ�����
int n=50000;//�����С�������������Ŀ
void output(char *s,int m)
{
    FILE *fp;//�������õ������������dat�ļ�����
    fp=fopen(s,"w");//��ֻд��ʽ����dat�ļ�
    fprintf(fp,"f={");//������������浽dat�ļ��У���mathematica��ͼ��������mathematica�﷨
    for(int i=1;i<n;i++)
    {
        fprintf(fp,"%lf,",(double)f[i]/m);//����ֻ��n���������������{f[i],f[i+1]}���ݵ㣬��Ϊ��ѹ���ļ���С
    }
    fprintf(fp,"%lf}",(double)f[n]/m);//�����ļ���ϣ�ʣ�¹�����mathematica��ȡ�����Լ���ͼ
    fclose(fp);
}
int main()
{
    int m=2147483647;
    int a=16807;
    int q=m/a;//q=m/aȡ��
    int r=m%a;//r=m/a������
    int i,seed;//seed���ڴ�������ֵ
    printf("��16807����������50000�������\n");
    printf("����������ֵ(0~%d)\n",m-1);
    scanf("%d",&seed);//���û���������ֵ
    f[0]=seed;//����ֵ
    for(i=1;i<=n;i++)//��Schrage��������n���������
    {
        if((a*(f[i-1]%q)-r*(f[i-1]/q))>0)//�ж��Ƿ����0
        {
            f[i]=a*(f[i-1]%q)-r*(f[i-1]/q);//����0���
        }
        else
            f[i]=a*(f[i-1]%q)-r*(f[i-1]/q)+m;//С��0���
    }//������������
    output("Schrage.dat",m);//������������ļ���
    printf("������\n(�س��˳�����)");
    char c;
    while((c=getchar())!='\n'&&c!=EOF);//��ջ�����
    c=getchar();//�ó�����ͣ�����Զ�����
    return 0;
}
