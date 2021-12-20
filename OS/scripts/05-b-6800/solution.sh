#!/bin/bash

DIR=$1
HIDDEN=0

if ! test -z $2 && test $2 = "-c"
then
	HIDDEN=1
fi

FILES=$(find $DIR -maxdepth 1 -printf "%p %s \n")

function is_hidden {
	FILENAME=$(basename $1)

	case $FILENAME in
		.*)
			return 0
			;;
		*)
			return 1
	esac
}


while read LINE
do
	FILE=$(echo $LINE | cut -d " " -f 1)

	if is_hidden $FILE && test $HIDDEN -eq 0
	then
		continue
	fi
	
	if test -f $FILE
	then
		echo $LINE
	elif test -d $FILE
	then
		echo $FILE" "$(find $FILE -maxdepth 1 | tail -n +2 | wc -l)
	fi

done < <(find $DIR -maxdepth 1 -printf "%p %s\n" | tail -n +2)
