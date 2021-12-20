#!/bin/bash

while test $# -gt 0
do
	if test -f $1
	then
		if cat $1 1>/dev/null 2> /dev/null
		then
			echo "We can read $1"
		else
			echo "We can't read $1"
		fi
	fi

	if test -d $1
	then
		FILECOUNT=$(find $1 -maxdepth 1 -type f | tail -n +2 | wc -l)
		find $1 -maxdepth 1 -type f -size -${FILECOUNT}c 
	fi
	shift
done
