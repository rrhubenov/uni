#!/bin/bash

if [[ "$1" =~ [^0-9A-Za-z]+ ]]; then
	echo "NOT OKAY"
else
	echo "OKAY"
fi
