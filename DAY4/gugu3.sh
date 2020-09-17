
x=1
while((x<10));
do printf "%2d x %2d = %2d\n" $1 $x $(($1*$x)); ((x++));
done

