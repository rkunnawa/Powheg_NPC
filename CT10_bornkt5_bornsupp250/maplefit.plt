#try to fit with maple
# read in the data points with errors fo rapidity bin 1.0 < | y |< 1.5

f(x)= a0*pow(x/a3,-a1)*pow(1-x/a3,a2)
fit [21,1024] f(x) 'datapoints_test_maplefit.dat' using ($2):($3):($4) via a0,a1,a2,a3
