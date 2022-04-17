# 10 files fix N
for var in {5000..25000..5000}
do
	file=./tests/test_fix_N_$(printf "%.5d" $var)
	./tests/test $var $var 100 > $file
	echo "Make "$file
done
# 9 files fix size
for var in {150..15000..150}
do
	if [ $((15000 % $var)) -eq 0 ]; then
		file=./tests/test_fix_size_$(printf "%.5d" $var)
		./tests/test 15000 15000 $var > $file
		echo "Make "$file
	fi
done
# fix N and fix size 
./tests/test 20000 20000 100 > ./tests/test_fix_Nsize
echo "Make ./tests/test_fix_Nsize"
echo "----Finish to Make Test Files----"