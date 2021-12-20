#!/bin/bash

N=$1
LI=$2
RI=$3

if [[ $N =~ ^[^0-9] || $LI =~ ^[^0-9] || $RI =~ ^[^0-9] ]]; then
	exit 3
fi

if test $LI -gt $RI; then
	exit 2
fi

if test $LI -le $N -a $N -le $RI; then
	exit 0
else
	exit 1
fi


