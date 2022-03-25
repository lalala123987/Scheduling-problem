function [S] = HRRN(m,N)%m为服务器数量，N为任务数量
%产生数据
M = zeros(1,m);      %服务器时间
%生成任务到达时间A(泊松分布)
Lambda = 10; %任务时间平均分布
A = random('Poisson',Lambda,1,N);  %生成1*N矩阵
A = A-min(A);
%生成任务加工时间T（高斯分布）
T = normrnd(Lambda,2,[1,N])/2;       %生成1*N矩阵
R = ones(1,N);   %初始化响应比矩阵
%高响应比优先
i=1;
last = 0;
Before = 0;
ADD = 0;
while i<=N
    [~,xu] = sort(R,'descend');  %对响应比矩阵排序
    if (i-last)==1
        [~,MINn] = min(M);  %当前时间
    end
    last = i;
%    [MIN,MINn] = min(M);   %MIN为当前时间，MINn为空闲服务器序号
    if A(xu(1))>M(MINn)
        M(MINn) = M(MINn)+0.1;  %如无任务，则等待0.1
    else
        Before = M(MINn);
        M(MINn) = M(MINn)+T(xu(1));
        [MIN,~] = min(M);
        ADD  =M(MINn)-Before;   %排队的任务需要增加的等待时间
        R(xu(1))=-99999;
        for j = 1:N
            if A(j)<Before   %所有正在排队的任务
                R(j) = R(j)+ADD/A(j);
            end
        end
        i = i+1;
    end 
end
C = max(M);
S=N/m/C;
end
