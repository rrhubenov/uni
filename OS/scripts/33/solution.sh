#!/bin/bash

N=10

if test $# -ge 1 && test $1 = '-n'
then
	shift
	N=$1
	shift
fi

IDFS=""

while test $# -ge 1
do	
	FILE=$1
	IDF="$(echo $1 | sed "s/\..*//")"

	tail $FILE -n $N | awk -v IDF="$IDF" '{print $1 " " $2 " " IDF " " $3 }'
	shift
done 





