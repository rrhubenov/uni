#!/bin/bash

FILE=$1
DIR=$2

for F in $(find $DIR -type f)
do
	if diff -q $F $FILE > /dev/null; then
		echo $F
	fi
done

