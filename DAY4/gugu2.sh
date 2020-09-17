
x=1
while((x<10));
do
printf "\n";
y=1
while((y<10));
do printf "%2d x %2d = %2d  " $x $y $(($x*$y)); ((y++));
done
((x++));
printf "\n";
done

