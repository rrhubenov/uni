#!/bin/bash

FILE=$1
DEPTH=0
MAX_DEPTH=0

for BRACKET in $(grep -e [{}] -o $FILE)
do
	if test $BRACKET  = "{"; then
		DEPTH=$((DEPTH + 1))
	fi
	if test $BRACKET = "}"; then
		DEPTH=$((DEPTH - 1))
	fi

	if test $DEPTH -gt $MAX_DEPTH; then
		MAX_DEPTH=$DEPTH
	fi
done

echo $MAX_DEPTH

