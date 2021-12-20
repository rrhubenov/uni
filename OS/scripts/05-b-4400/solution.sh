#!/bin/bash

DIR_FROM=$1
DIR_TO_DEFAULT=$(date +%d-%m-%y)

if [ $# -lt 2 ]; then
	DIR=$DIR_TO_DEFAULT
else
	DIR=$2
fi

mkdir $DIR

for FILE in $(find $DIR_FROM -maxdepth 1 -type f -amin -45)
do
	cp $FILE $DIR
done

	
