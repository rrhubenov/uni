#!/bin/bash


DIRECTORY=$1

echo DIRECTORIES: $(find $DIRECTORY -maxdepth 1 -type d | wc -l)
echo FILES: $(find $DIRECTORY -maxdepth 1 -type f | wc -l)
