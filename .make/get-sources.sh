#!/bin/bash

SRC_PATH=./src

if [ $1 ] && [ -d $1 ]; then
	SRC_PATH=$1;
elif [ $1 ]; then
	echo "ERROR: $1 is not a directory (using $SRC_PATH instead)." >&2
fi

echo "SRC_DIRS := \\"
find $SRC_PATH -type d -exec echo -e "\t\t\t\t\t{} \\" \;

echo

echo "SRCS := \\"
find $SRC_PATH -type f -name "*.c" -exec echo -e "\t\t\t\t\t{} \\" \;

echo
