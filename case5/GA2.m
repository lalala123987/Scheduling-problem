function [SS] = GA2(m,N,G,L)
%m为服务器数量，N为任务数量,P为遗传代数,L为种群大小
Pcross = 0.4;
Pmutation = 0.01;
%产生数据

%生成任务到达时间A(泊松分布)
Lambda = 10; %任务到达时间平均值
A = random('Poisson',Lambda,1,N);  %生成1*N矩阵
A = A-min(A);
%生成任务加工时间T（高斯分布）
T = normrnd(Lambda,2,[1,N])/2;       %生成1*N矩阵

Population = zeros(N,L);  %初始化L大小的种群
for l=1:L
    Population(:,l) = randperm(N);   %随机生成L大小的种群
end
SS = zeros(1,G);
for gener = 1:G
    M = zeros(L,m);      %服务器时间
    for i = 1:L
        j = 1;
        last = 0;
        while j<=N
            if (j-last)==1
                [~,MINn] = min(M(i,:));  %当前时间
            end
            last = j;
            if M(i,MINn)<A(Population(j,i))
                M(i,MINn) = M(i,MINn)+0.1;
            else
                M(i,MINn) = M(i,MINn) + T(Population(j,i));
                j = j+1;
            end
        end
    end
    C = max(M,[],2);
    S = N/m./C;
    SS(gener) = max(S);
    p = S./sum(S);
    P = cumsum(p);

    R = rand(1,L);
    Population1 = zeros(N,L);
    [~,elite] = max(S);   %精英
    for K = 1:L
        for x = 1:L-1
            if ((R(K)>=P(x)&&R(K)<P(x+1))||(R(K)<=P(1)))
                Population1(:,K) = Population(:,x);
            end
        end
    end
    y=1;
    R1 = randi([1,N],1,L);
    Population2 = zeros(N,L);
    while y<L          %cross
        if rand()< Pcross
            MID1 = Population1(:,y);
            MID2 = Population1(:,y+1);
            for RY = R1(y):N
                del = Population1(RY,y+1);
                MID1(MID1 ==del) =[];
            end
            for RY = R1(y):N
                del = Population1(RY,y);
                MID2(MID2 ==del) =[];
            end
            Population2(:,y) = [Population1(R1(y):end,y+1);MID1];
            Population2(:,y+1) = [Population1(R1(y):end,y);MID2];
        else
            Population2(:,y) = Population1(:,y);
            Population2(:,y+1) = Population1(:,y+1);
        end
        y = y+2;
    end
    %基因突变
    for mutY = 1:L
        if rand() <Pmutation
            R2 = randi([1,N-3],1,1);
            mid = Population2(R2,mutY);
            Population2(R2,mutY) = Population2(R2+3,mutY);
            Population2(R2,mutY) = mid;
        end
    end
    Population2(:,L) = Population(:,elite) ;
    Population = Population2;
end
end