#!/bin/bash

DIR=$1
SIZE=$2

find $DIR -maxdepth 1 -type f -size +${SIZE}c -printf "%p\n"
