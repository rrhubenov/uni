#!/bin/bash


FILE=$1
STRING=$2

if grep "$STRING" $FILE -q ; then
	grep "$STRING" $FILE
else
	echo "String not found in file"
fi
