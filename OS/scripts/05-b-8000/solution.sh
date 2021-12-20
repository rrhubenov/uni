#!/bin/bash

USER=$1

while read PROCMEM
do
	read VSZ RSS < <(echo $PROCMEM)
	MEM=$(echo "scale=2; $RSS/$VSZ" | bc)

	echo $MEM

done < <(ps -u $USER -o vsz= -o rss= | sort -n)
