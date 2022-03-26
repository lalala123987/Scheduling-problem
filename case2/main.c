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
int* Manual(int N);                         //�ֶ���������ʱ��
int* Auto(int N, int max);                  //�Զ���������ʱ��
int* p0;                                    //����ʱ������ָ��
int* p2;                                    //�����ֹʱ��ָ��
int* FCFS(int* p0, int* p2, int N);         //FCFS�㷨����������������ʱ��ָ��
int* SJF(int* p0, int* p2, int N);          //SJF�㷨����������������ʱ��ָ��
int* EDD(int* p0, int* p2, int N);          //EDD �㷨����������������ʱ��ָ��
int shellSort(int *p, int* p1, int N);      //ϣ������

int main() {
    int* L;
    int N = 0,type,ALG,i;
    int state = 0;
    printf("��������������:\n");
    scanf("%d",&N);  //��ȡ��������N
    p0 = (int * ) malloc(N* sizeof(int));
    p2 = (int * ) malloc(N* sizeof(int));
    //��������ӹ�ʱ��
    while (state == 0){
        printf("�ֶ���������ʱ������������1���Զ���������ʱ������������2��\n");
        scanf("%d",&type);
        if (type==1){
            p0 = Manual(N);
            state = 1;
        }
        else if (type==2){
            p0 = Auto(N,21);
            state = 1;
        }
        else
            printf("��������ȷ�����ݣ�\n");
    }
    printf("����ʱ�䣺\n");
    for (i = 0; i < N; i++)
        printf("��%d������:%d\n",i+1,p0[i]);
    state = 0;
    //���������ֹʱ��
    while (state == 0){
        printf("�ֶ����������ֹʱ������������1���Զ����������ֹʱ������������2��\n");
        scanf("%d",&type);
        if (type==1){
            p2 = Manual(N);
            state = 1;
        }
        else if (type==2){
            p2 = Auto(N,41);
            state = 1;
        }
        else
            printf("��������ȷ�����ݣ�\n");
    }
    printf("�����ֹʱ�䣺\n");
    for (i = 0; i < N; i++)
        printf("��%d������:%d\n",i+1,p2[i]);
    state = 0;

    while (state == 0){
        printf("ʹ��FCFS�㷨������1��ʹ��SJF�㷨������2��ʹ��EDD�㷨������3��\n");
        scanf("%d",&ALG);
        if (ALG == 1){
            L = FCFS(p0,p2,N);
            state = 1;
        } else if (ALG == 2){
            L = SJF(p0,p2,N);
            state = 1;
        } else if (ALG == 3){
            L = EDD(p0,p2,N);
            state = 1;
        } else
            printf("��������ȷ�����ݣ�\n");
    }
    printf("����������ʱ�䣺\n");
    for (i = 0; i < N; i++)
        printf("��%d������:%d\n",i+1,p0[i]);
    printf("�����������ӳ٣�\n");
    for (int j = 0; j < N; ++j) {
        printf("��%d������%d\n",j+1,L[j]);
    }
    shellSort(L, p0, N); //����p0ֻ��Ϊ��ռλ������ʵ������
    printf("Lmax��ֵΪ��%d",L[N-1]);
    return 0;
}

int* Manual(int N){
    int* p;
    p = (int * ) malloc(N* sizeof(int));
    for (int i = 0; i < N; ++i) {
        printf("�������%d����������ݣ�",i+1);
        scanf("%d",&p[i]);
    }
    return p;
}

int* Auto(int N,int max){
    int* p;
    p = (int * ) malloc(N* sizeof(int));
    srand((unsigned int)time(0));//�޸�����
    for (int i = 0; i < N; i++)
    {
        p[i] = (rand()%max)+1;//���÷�Χ  1-20
        Sleep(5);
    }
    return p;
}

int* FCFS(int *p0, int* p2, int N) {
    int* L;
    int* S;
    S = (int * ) malloc(N* sizeof(int));
    L = (int * ) malloc(N* sizeof(int));
    int count = 0;
    for (int j = 0; j < N; ++j) {
        S[j] = 0;
        for (int k = 0; k <= j; ++k) {
            S[j] = S[j] + p0[k];
            count++;
        }
    }
    for (int i = 0; i < N; ++i) {
        L[i] = S[i] - p2[i];
        count++;
    }
    printf("FCFS�㷨�������������%d\n",count); //��ӡ�ܵȴ�ʱ������������
    return L;
}

int* SJF(int* p0, int* p2, int N){
    int* S;
    int* L;
    S = (int * ) malloc(N* sizeof(int));
    L = (int * ) malloc(N* sizeof(int));
    int count = shellSort(p0, p2, N);
    for (int j = 0; j < N; ++j) {
        S[j] = 0;
        for (int k = 0; k <= j; ++k) {
            S[j] = S[j] + p0[k];
            count++;
        }
    }
    for (int i = 0; i < N; ++i) {
        L[i] = S[i] - p2[i];
        count++;
    }
    printf("SJF�㷨�������������%d\n",count); //��ӡ�ܵȴ�ʱ������������
    return L;
}

int* EDD(int *p0, int* p2, int N) {
    int* S;
    S = (int * ) malloc(N* sizeof(int));
    int count = shellSort(p2, p0, N);
    for (int i = 0;i < N; ++i){
        S[i] = 0;
        for (int j = 0; j <= i; ++j)
            S[i] = S[i] + p0[j];    //�õ�ÿ����������ʱ��
    }
    int L = 0;
    for (int k = 0; k < N; ++k){
        S[k] = S[k]-p2[k];        //�����ӳ�
    }
    printf("EDD�㷨�������������%d\n",count); //��ӡ���������
    return S;
}

int shellSort(int *p, int* p1, int N){
    //ϣ������
    int count = 0;
    for (int gap = N/2; gap>0; gap/=2){       //��ʼ����gap����ΪN��һ�룬���𲽳�2��С����
        for (int i =gap; i<N; i++){           //���ǵ�ÿһ����
            int j = i;
            while (j-gap>=0&&p[j]<p[j-gap]){  //���ڽ�������
                int swap = p[j];
                int swap1 = p1[j];  //���ڵڶ����������ͬ������
                p[j] = p[j-gap];
                p1[j] = p1[j-gap];
                p[j-gap] = swap;
                p1[j-gap] = swap1;
                j -= gap;
                count++;
            }
        }
    }
    return count;
}