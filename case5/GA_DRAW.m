G=3000;L=300;m=10;N=20;SUM = zeros(1,G);
parfor i = 1:20
    SUM = SUM+GA2(m,N,G,L);
end

middle=SUM./20;
plot(middle);