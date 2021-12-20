#!/bin/bash


DIR=$1
FILES=$(find $DIR -maxdepth 1 -type f)

for TARGET_FILE in $FILES
do
	SAMEFILES=""
	for FILE in $FILES
	do
		if diff $TARGET_FILE $FILE > /dev/null
		then
			SAMEFILES=$SAMEFILES'\n'$FILE
		fi
	done

	while read FILE
	do
		rm $FILE
	done < <(echo -e $SAMEFILES | sort | tail -n +2)

done

exit 0
			
			
