rm ans
g++ orig.cpp -O2 && ./a.out $1 > ans && sort -nc ans
test $? -eq 0 && echo "OK" || echo "WA"