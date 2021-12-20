#!/bin/bash

USERID=$1

while true
do

	if ! test -z "$(w $1 -h)"; then
		echo $1 HAS LOGGED IN
		exit 0
	fi	

	sleep 1
done
