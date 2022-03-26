#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <synchapi.h>
/* 案例2
 * 要求：
 * N个任务，具有不同任务时长,有不同截止时间
 * 使总延迟L最小
 *
 * 使用算法：
 * FCFS、SJF、EDD
 *
 * 程序输出：
 * 1.输入的每个任务时长
 * 2.排序后的顺序
 * 3.总等待时间
 * 4.总运算次数
 */
int* Manual(int N);                         //手动输入任务时长
int* Auto(int N, int max);                  //自动生成任务时长
int* p0;                                    //任务时间数组指针
int* p2;                                    //任务截止时间指针
int* FCFS(int* p0, int* p2, int N);         //FCFS算法，返回排序后的任务时间指针
int* SJF(int* p0, int* p2, int N);          //SJF算法，返回排序后的任务时间指针
int* EDD(int* p0, int* p2, int N);          //EDD 算法，返回排序后的任务时间指针
int shellSort(int *p, int* p1, int N);      //希尔排序

int main() {
    int* L;
    int N = 0,type,ALG,i;
    int state = 0;
    printf("请输入任务数量:\n");
    scanf("%d",&N);  //获取服务数量N
    p0 = (int * ) malloc(N* sizeof(int));
    p2 = (int * ) malloc(N* sizeof(int));
    //产生任务加工时间
    while (state == 0){
        printf("手动输入任务时间数据则输入1，自动生成任务时间数据则输入2：\n");
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
            printf("请输入正确的数据！\n");
    }
    printf("任务时间：\n");
    for (i = 0; i < N; i++)
        printf("第%d个任务:%d\n",i+1,p0[i]);
    state = 0;
    //产生任务截止时间
    while (state == 0){
        printf("手动输入任务截止时间数据则输入1，自动生成任务截止时间数据则输入2：\n");
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
            printf("请输入正确的数据！\n");
    }
    printf("任务截止时间：\n");
    for (i = 0; i < N; i++)
        printf("第%d个任务:%d\n",i+1,p2[i]);
    state = 0;

    while (state == 0){
        printf("使用FCFS算法请输入1，使用SJF算法请输入2，使用EDD算法请输入3：\n");
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
            printf("请输入正确的数据！\n");
    }
    printf("排序后的任务时间：\n");
    for (i = 0; i < N; i++)
        printf("第%d个任务:%d\n",i+1,p0[i]);
    printf("排序后的任务延迟：\n");
    for (int j = 0; j < N; ++j) {
        printf("第%d个任务：%d\n",j+1,L[j]);
    }
    shellSort(L, p0, N); //其中p0只是为了占位，而无实际意义
    printf("Lmax的值为：%d",L[N-1]);
    return 0;
}

int* Manual(int N){
    int* p;
    p = (int * ) malloc(N* sizeof(int));
    for (int i = 0; i < N; ++i) {
        printf("请输入第%d个任务的数据：",i+1);
        scanf("%d",&p[i]);
    }
    return p;
}

int* Auto(int N,int max){
    int* p;
    p = (int * ) malloc(N* sizeof(int));
    srand((unsigned int)time(0));//修改种子
    for (int i = 0; i < N; i++)
    {
        p[i] = (rand()%max)+1;//设置范围  1-20
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
    printf("FCFS算法的总运算次数：%d\n",count); //打印总等待时间和总运算次数
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
    printf("SJF算法的总运算次数：%d\n",count); //打印总等待时间和总运算次数
    return L;
}

int* EDD(int *p0, int* p2, int N) {
    int* S;
    S = (int * ) malloc(N* sizeof(int));
    int count = shellSort(p2, p0, N);
    for (int i = 0;i < N; ++i){
        S[i] = 0;
        for (int j = 0; j <= i; ++j)
            S[i] = S[i] + p0[j];    //得到每个任务的完成时间
    }
    int L = 0;
    for (int k = 0; k < N; ++k){
        S[k] = S[k]-p2[k];        //计算延迟
    }
    printf("EDD算法的总运算次数：%d\n",count); //打印总运算次数
    return S;
}

int shellSort(int *p, int* p1, int N){
    //希尔排序
    int count = 0;
    for (int gap = N/2; gap>0; gap/=2){       //初始增量gap设置为N的一半，并逐步除2缩小增量
        for (int i =gap; i<N; i++){           //覆盖到每一个组
            int j = i;
            while (j-gap>=0&&p[j]<p[j-gap]){  //组内交换排序
                int swap = p[j];
                int swap1 = p1[j];  //对于第二个数组进行同步调换
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