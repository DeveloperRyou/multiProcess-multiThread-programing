# 50 files fix N
for var in {500..25000..500}
do
	file=./tests/test_fix_N_$(printf "%.5d" $var)
	./tests/test $var $var 10 > $file
	echo "Make "$file
done
# 30 files fix size
for var in {1..20000..1}
do
	if [ $((20000 % $var)) -eq 0 ]; then
		file=./tests/test_fix_size_$(printf "%.5d" $var)
		./tests/test 20000 20000 $var > $file
		echo "Make "$file
	fi
done
# fix N and fix size 
./tests/test 25000 25000 10 > ./tests/test_fix_Nsize
echo "Make ./tests/test_fix_Nsize"
echo "----Finish to Make Test Files----"