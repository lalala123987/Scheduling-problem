#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <synchapi.h>

/* ����2
 * Ҫ��
 * N�����񣬾��в�ͬ����ʱ��,�в�ͬ��ֹʱ��
 * ʹ���ӳ�L��С
 *
 * ʹ���㷨��
 * FCFS��SJF��EDD
 *
 * ���������
 * 1.�����ÿ������ʱ��
 * 2.������˳��
 * 3.�ܵȴ�ʱ��
 * 4.���������
 */
void Manual(int N);               //�ֶ���������ʱ��
void Auto(int N);                 //�Զ���������ʱ��
int* p0;                          //����ʱ������ָ��
int* p1;                          //�㷨����������ʱ��ָ��
int* FCFS(int* p, int N);         //FCFS�㷨����������������ʱ��ָ��
int* SJF(int* p, int N);          //SJF�㷨����������������ʱ��ָ��
int shellSort(int *p, int N);     //ϣ������
int OperateNum = 0;               //���������������

int main() {
    int N = 0,type,ALG,i;
    int state = 0;
    printf("��������������:\n");
    scanf("%d",&N);  //��ȡ��������N
    p0 = (int * ) malloc(N* sizeof(int));
    p1 = (int * ) malloc(N* sizeof(int));
    while (state == 0){
        printf("�ֶ���������ʱ������������1���Զ���������ʱ������������2��\n");
        scanf("%d",&type);
        if (type==1){
            Manual(N);
            state = 1;
        }
        else if (type==2){
            Auto(N);
            state = 1;
        }
        else
            printf("��������ȷ�����ݣ�\n");
    }
    printf("����ʱ�䣺\n");
    for (i = 0; i < N; i++)
        printf("��%d������:%d\n",i+1,p0[i]);
    state = 0;
    while (state == 0){
        printf("ʹ��FCFS�㷨������1��ʹ��SJF�㷨������2");
        scanf("%d",&ALG);
        if (ALG == 1){
            p1 = FCFS(p0,N);
            state = 1;
        } else if (ALG == 2){
            p1 = SJF(p0,N);
            state = 1;
        }  else
            printf("��������ȷ�����ݣ�\n");
    }
    printf("����������ʱ�䣺\n");
    for (i = 0; i < N; i++)
        printf("��%d������:%d\n",i+1,p1[i]);
    return 0;
}

void Manual(int N){
    for (int i = 0; i < N; ++i) {
        printf("�������%d�����������ʱ�䣺",i+1);
        scanf("%d",&p0[i]);
    }
}

void Auto(int N){
    srand((unsigned int)time(0));//�޸�����
    for (int i = 0; i < N; i++)
    {
        p0[i] = (rand()%21)+1;//���÷�Χ  1-20
        Sleep(5);
    }
}

int *FCFS(int *p, int N) {
    int count = 0;
    int C = 0;
    for (int i = 0; i < N; ++i) C = C + (N-i)*p[i];  //�����ܵȴ�ʱ��C
    printf("FCFS�㷨���ܵȴ�ʱ��C��%d\nFCFS�㷨�������������%d\n",C,count); //��ӡ�ܵȴ�ʱ������������
    return p;
}

int *SJF(int* p, int N){
    int count = shellSort(p, N);
    int C = 0;
    for (int i = 0; i < N; ++i) C = C + (N-i)*p[i];  //�����ܵȴ�ʱ��C
    printf("SJF�㷨���ܵȴ�ʱ��C��%d\nSJF�㷨�������������%d\n",C,count); //��ӡ�ܵȴ�ʱ������������
    return p;
}

int shellSort(int *p, int N){
    //ϣ������
    int count = 0;
    for (int gap = N/2; gap>0; gap/=2){       //��ʼ����gap����ΪN��һ�룬���𲽳�2��С����
        for (int i =gap; i<N; i++){           //���ǵ�ÿһ����
            int j = i;
            while (j-gap>=0&&p[j]<p[j-gap]){  //���ڽ�������
                int swap = p[j];
                p[j] = p[j-gap];
                p[j-gap] = swap;
                j -= gap;
                count++;
            }
        }
    }
    return count;
}

