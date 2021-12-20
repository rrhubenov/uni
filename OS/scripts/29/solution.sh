#!/bin/bash
# 


LGODIR
	prot1
		acc1
			buddy1
				yyyy-mm-dd-hh-mm-ss.txt
			buddy2
		acc2
			buddy1
	prot2
	prot3


p='????-??-??-??-??-??.txt'

for b in $(find -- ${LOGDIR} -mindepth 3 -maxdepth 3 -type d -exec basename {} \; | sort |uniq); do

	echo "$(cat $LOGDIR/*/*/${b}/${p} | wc -l) ${b}"
done | sort -rn | head 
