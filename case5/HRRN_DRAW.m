DRAW = zeros(1,10000);
MEAN = zeros(10,10);
for m=10:10:100
    for N = m+10:10:100
        parfor i=1:10000
            DRAW(i) = HRRN(m,N);
        end
        MEAN(m/10,N/10) = mean(DRAW);
    end
end
X = 10:10:100;
Y = 10:10:100;
surf(X,Y,MEAN);