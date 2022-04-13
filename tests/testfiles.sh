# 20 files fix N
for var in {250..5000..250}
do
	file=./tests/test_fix_N_$(printf "%.4d" $var)
	./tests/test $var $var 10 > $file
	echo "Make "$file
done
# 20 files fix size
for var in {1..5000..1}
do
	if [ $((5000 % $var)) -eq 0 ]; then
		file=./tests/test_fix_size_$(printf "%.4d" $var)
		./tests/test 5000 5000 $var > $file
		echo "Make "$file
	fi
done
# fix N and fix size 
./tests/test 5000 5000 10 > ./tests/test_fix_Nsize
echo "Make ./tests/test_fix_Nsize"
echo "----Finish to Make Test Files----"