#!/bin/bash

function is_hidden {
	FILENAME=$(basename $1)

	case $FILENAME in
		.*)
			return 0
			;;
		*)
			return 1
	esac
}

if is_hidden ".asd"
then 
	echo "its hidden"
else
	echo "its not"
fi

