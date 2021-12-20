#!/bin/bash

read -p "Enter a string: " STRING

while test $# -gt 0
do
	FILE=$1

	COUNT=$(grep "$STRING" $FILE | wc -l) 

	echo $FILE: $COUNT

	shift
done
