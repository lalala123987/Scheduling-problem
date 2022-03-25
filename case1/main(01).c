#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <synchapi.h>

/* 案例1
 * 要求：
 * N个任务，具有不同任务时长
 * 使总等待时间C最小
 *
 * 使用算法：
 * FCFS、SJF
 *
 * 程序输出：
 * 1.输入的每个任务时长
 * 2.排序后的顺序
 * 3.总等待时间
 * 4.总运算次数
 */
void Manual(int N);               //手动输入任务时长
void Auto(int N);                 //自动生成任务时长
int* p0;                          //任务时间数组指针
int* p1;                          //算法排序后的任务时间指针
int* FCFS(int* p, int N);          //SJF算法，返回排序后的任务时间指针
int* SJF(int* p, int N);          //SJF算法，返回排序后的任务时间指针
int shellSort(int *p, int N);    //希尔排序
int OperateNum = 0;               //排序运算操作次数

int main() {
    int N = 0,type,ALG,i;
    int state = 0;
    printf("请输入任务数量:\n");
    scanf("%d",&N);  //获取服务数量N
    p0 = (int * ) malloc(N* sizeof(int));
    p1 = (int * ) malloc(N* sizeof(int));
    while (state == 0){
        printf("手动输入任务时间数据则输入1，自动生成任务时间数据则输入2：\n");
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
            printf("请输入正确的数据！\n");
    }
    printf("任务时间：\n");
    for (i = 0; i < N; i++)
        printf("第%d个任务:%d\n",i+1,p0[i]);
    state = 0;
    while (state == 0){
        printf("使用FCFS算法请输入1，使用SJF算法请输入2");
        scanf("%d",&ALG);
        if (ALG == 1){
            p1 = FCFS(p0,N);
            state = 1;
        } else if (ALG == 2){
            p1 = SJF(p0,N);
            state = 1;
        }  else
            printf("请输入正确的数据！\n");
    }
    printf("排序后的任务时间：\n");
    for (i = 0; i < N; i++)
        printf("第%d个任务:%d\n",i+1,p1[i]);
    return 0;
}

void Manual(int N){
    for (int i = 0; i < N; ++i) {
        printf("请输入第%d个任务的任务时间：",i+1);
        scanf("%d",&p0[i]);
    }
}

void Auto(int N){
    srand((unsigned int)time(0));//修改种子
    for (int i = 0; i < N; i++)
    {
        p0[i] = (rand()%21)+1;//设置范围  1-20
        Sleep(5);
    }
}

int *FCFS(int *p, int N) {
    int count = 0;
    int C = 0;
    for (int i = 0; i < N; ++i) C = C + (N-i)*p[i];  //计算总等待时间C
    printf("FCFS算法的总等待时间C：%d\nFCFS算法的总运算次数：%d\n",C,count); //打印总等待时间和总运算次数
    return p;
}

int *SJF(int* p, int N){
    int count = shellSort(p, N);
    int C = 0;
    for (int i = 0; i < N; ++i) C = C + (N-i)*p[i];  //计算总等待时间C
    printf("SJF算法的总等待时间C：%d\nSJF算法的总运算次数：%d\n",C,count); //打印总等待时间和总运算次数
    return p;
}

int shellSort(int *p, int N){
    //希尔排序
    int count = 0;
    for (int gap = N/2; gap>0; gap/=2){       //初始增量gap设置为N的一半，并逐步除2缩小增量
        for (int i =gap; i<N; i++){           //覆盖到每一个组
            int j = i;
            while (j-gap>=0&&p[j]<p[j-gap]){  //组内交换排序
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

