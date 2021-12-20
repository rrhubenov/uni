#!/bin/bash

NUM=$(( ($RANDOM % 100) + 1  ))
TRIES=1

while read GUESS
do
	if test $GUESS -gt $NUM
	then
		echo "SMALLER"
	elif test $GUESS -lt $NUM
	then
		echo "BIGGER"
	else
		echo "CORRECT! WITH $TRIES TRIES"
		break
	fi
	TRIES=$(( $TRIES + 1))
done


