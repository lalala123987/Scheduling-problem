function [S] = FCFS(m,N)%m为服务器数量，N为任务数量
%产生数据
M = zeros(1,m);      %服务器时间
%生成任务到达时间A(泊松分布)
Lambda = 10; %任务时间平均分布
A = random('Poisson',Lambda,1,N);  %生成1*N矩阵
A = A-min(A);
%生成任务加工时间T（高斯分布）
T = normrnd(Lambda,2,[1,N])/2;       %生成1*N矩阵

%先来先服务
[~,xu] = sort(A); %对任务到达时间进行排序
i=1;
last = 0;
while i<=N
    if (i-last)==1
        [~,MINn] = min(M);  %当前时间
    end
    last = i;
    if MIN<A(xu(i))
        M(MINn) = M(MINn)+0.1;
        i = i-1; 
    else
        M(MINn) = M(MINn) + T(xu(i));
    end
    i = i+1;
end
C = max(M);
S=N/m/C;
end

