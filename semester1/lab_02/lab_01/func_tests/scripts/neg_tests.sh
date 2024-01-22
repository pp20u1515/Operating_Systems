#!/bin/bash

main_func()
{
    echo -e "\tNegative Tests:"
    echo

	num=1 # counter
	green_col=$'\e[32mPASSED\e[0m' # green color
	red_col=$'\e[31mFAILED\e[0m' # red color

	while [[ "$num" -lt 10 ]]; do
		echo "TEST 0${num}:"
		
		../../app.exe < ../data/neg_0${num}_in.txt > ../data/out.txt

		rc=$? 

		if diff -Z "../data/neg_0${num}_out.txt" "../data/out.txt" && [ $rc -ne 0 ]; then 
			echo "neg_0${num}.txt: " "${green_col}"
		else
			echo "neg_0${num}.txt: " "${red_col}"
		fi
		
		echo
		(( num++ )) #counter increase
	done
}

main_func
rm ../data/out.txt