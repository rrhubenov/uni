#!/bin/bash


DIR=$1
FILES=$(find $DIR -maxdepth 1 -type f)

for TARGET_FILE in $FILES
do
	
	if ! test -e $TARGET_FILE
	then
		continue
	fi

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
	done < <(echo -e $SAMEFILES | sort | tail -n +3)
	FILES=$(find $DIR -maxdepth 1 -type f)
done

exit 0
			
			
