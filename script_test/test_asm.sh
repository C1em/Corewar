#!/bin/bash

rm test/*.cor
set -eux

for f in test/*.s
do
	./asm_test $f
	cp $f test/test.s
	./asm test/test.s
	COR=$(echo $f | sed 's/.$/cor/g')
	DIFF=$(cmp test/test.cor $COR)
	if [ -n "$DIFF" ]
	then 
		echo "AIE !"
		exit 1
	fi
	rm test/test.cor test/test.s
done
