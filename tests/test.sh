# test many size
for file in $(ls ./tests/ | grep test_fix_N_)
do
	echo $file | tr '\n' '\t' >> ./tests/test_fix_N_output
	./program1 avg < ./tests/$file | head -1 | tr '\n' '\t'  >> ./tests/test_fix_N_output
	./program2 avg 4 < ./tests/$file | head -1 | tr '\n' '\t' >> ./tests/test_fix_N_output
	./program3 avg 4 < ./tests/$file | head -1 >> ./tests/test_fix_N_output
done
# test many N
for file in $(ls ./tests/ | grep test_fix_size_)
do
	echo $file | tr '\n' '\t' >> ./tests/test_fix_size_output
	./program1 avg < ./tests/$file | head -1 | tr '\n' '\t'  >> ./tests/test_fix_size_output
	./program2 avg 4 < ./tests/$file | head -1 | tr '\n' '\t' >> ./tests/test_fix_size_output
	./program3 avg 4 < ./tests/$file | head -1 >> ./tests/test_fix_size_output
done
# test many process
for process in {1..60..1}
do
	file=test_fix_Nsize
	echo $file"_"$process | tr '\n' '\t' >> ./tests/test_fix_Nsize_output
	./program1 avg < ./tests/$file | head -1 | tr '\n' '\t'  >> ./tests/test_fix_Nsize_output
	./program2 avg $process < ./tests/$file | head -1 | tr '\n' '\t' >> ./tests/test_fix_Nsize_output
	./program3 avg $process < ./tests/$file | head -1 >> ./tests/test_fix_Nsize_output
done