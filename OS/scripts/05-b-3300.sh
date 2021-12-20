#!/bin/bash

FILE1=$1
FILE2=$2
FILE3=$3

paste $FILE1 $FILE2 | sort > $FILE3


