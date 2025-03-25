#!/bin/bash

shopt -s nocasematch

RETURN_VALUE=0

export GREEN="\033[0;32m"
export LIGHTGREEN="\033[1;32m"
export RED="\033[0;31m"
export LIGHTRED="\033[1;31m"
export YELLOW="\033[1;33m"
export DEFAULT="\033[0m"

function run_test() {
  # RETURN_VALUE=0
  # Test file-based input
  calabash_output=`echo "$COMMAND" | ../calabash`
  bash_output=`echo "$COMMAND" | bash`
  if [ "$calabash_output" = "$bash_output" ]; then
	echo -e -n "FILE:   [${GREEN}PASS${DEFAULT}] $COMMAND";
	echo -e -n "  --->  ";
	echo -e "'${LIGHTGREEN}$calabash_output${DEFAULT}'"
  else
	echo -e "FILE:   [${RED}FAIL${DEFAULT}] $COMMAND";
	echo -e   ${LIGHTRED}"calabash output:" "$calabash_output"${DEFAULT}
	echo -e ${LIGHTGREEN}"    bash output:" "$bash_output"${DEFAULT}
	RETURN_VALUE=1;
  fi

  # Test string-based input
  calabash_output=`../calabash -c "$COMMAND"`
  bash_output=`bash -c "$COMMAND"`
  if [ "$calabash_output" = "$bash_output" ]; then
	echo -e -n "STRING: [${GREEN}PASS${DEFAULT}] $COMMAND";
	echo -e -n "  --->  ";
	echo -e "'${LIGHTGREEN}$calabash_output${DEFAULT}'"
  else
	echo -e "STRING: [${RED}FAIL${DEFAULT}] $COMMAND";
	echo -e   ${LIGHTRED}"calabash output:" "$calabash_output"${DEFAULT}
	echo -e ${LIGHTGREEN}"    bash output:" "$bash_output"${DEFAULT}
	RETURN_VALUE=1;
  fi

  echo
}

export COMMAND="echo \$USER"
run_test

export COMMAND="echo \$USER \$PWD"
run_test

export COMMAND="echo '\$USER'"
run_test

export COMMAND="echo \"\$USER\""
run_test

export COMMAND="echo \"'\$USER'\""
run_test

export COMMAND="echo '\"\$USER\"'"
run_test



export COMMAND="echo \"   123   \" 444"
run_test

export COMMAND="echo abc'def'ghi"
run_test

export COMMAND="echo \"abc def ghi\""
run_test

export COMMAND="echo \" \""
run_test

export COMMAND="echo \"   \""
run_test

export COMMAND="echo \" abc\""
run_test

export COMMAND="echo \"def \""
run_test

export COMMAND="echo \" ghi \""
run_test

export COMMAND="echo \"abc def ghi\""
run_test

exit $RETURN_VALUE
