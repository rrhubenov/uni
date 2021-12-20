#!/bin/bash

COUNT=0

for BINPATH in $(echo $PATH | tr ":" " ")
do
	COUNT=$(($COUNT + $(find $BINPATH -maxdepth 1 -type f -executable | wc -l) ))
done

echo $COUNT


