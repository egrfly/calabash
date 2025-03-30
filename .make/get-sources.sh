#!/bin/bash

SRC_PATH=./src

if [[ $1 ]] && [[ -d $1 ]]; then
	SRC_PATH=$1;
else
	if [[ $1 ]]; then
		echo "ERROR: $1 is not a directory (using $SRC_PATH instead)." >&2
	fi
fi

echo "SRC_DIRS :=	"
find $SRC_PATH -type d -exec echo "			{}" \;

echo

echo "SRCS :=		"
find $SRC_PATH/ -name "*.c" -exec echo "			{}" \;

echo
