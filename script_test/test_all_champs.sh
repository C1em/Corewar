#!/bin/bash

for f in test/*.s
do
	./asm_test $f
done

DIFF=""

for f2 in test/*.cor
do
	for f3 in test/*.cor
	do
		echo "$f2 & $f3"
		./corewar $f2 $f3 > our
		./cw $f2 $f3 > real
		DIFF=$(cmp real our)
		if [ -n "$DIFF" ]
		then
			ERROR=$(head -1 our)
			if [ "$ERROR" != "Error" ]
			then
				echo " AIIIIIIEEEEEEE !!!!!!! : $f2 & $f3"
				exit 1
			fi
		fi
	done

done

echo "perfect !!!!!!!"
