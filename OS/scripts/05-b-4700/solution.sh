#!/bin/bash

NUMBER=$1

if test $# -gt 1; then
	DELIM=$2
else
	DELIM=" "
fi

OUTPUT=""

while test $NUMBER -gt 1000
do
	OUTPUT=$DELIM$(($NUMBER % 1000))$OUTPUT
	NUMBER=$(($NUMBER / 1000))
done

OUTPUT=$(($NUMBER % 1000))$OUTPUT


echo $OUTPUT


