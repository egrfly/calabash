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

export COMMAND="echo \$USER \$GROUP abc 123 abc123"
run_test

export COMMAND="no_such_cmd 2>/dev/null; echo \$?"
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

export COMMAND="export whois=\"some pople\"; echo \$whois"
run_test

export COMMAND="\"\$\$asfddasfsd\$USER|djafogisd\$user\$test\""
run_test

export COMMAND="\"\$\$1asfddasfsd\$USER|djafogisd\$user\$testuuuas2 2 32 32 \$MFLAGS 222222\""
run_test

export COMMAND="\"\$?\$USER'\$?\$PWD\"\$USER\"\$USER'\$?\"\$USER\"\$?\""
run_test

export COMMAND="\"\$? \"\$USER'\$?'\"'\$PWD' zzz '\$PWD'\$?ZERO!\""
run_test

export COMMAND="export v=\"     heee     looo   \"; echo \$v"
run_test

export COMMAND="export v=\"     heee     looo   \"; ls \$v"
run_test

export COMMAND="ls \"\""
run_test

export COMMAND="ec\"ho\""
run_test

export COMMAND="export LS=\"s -l\"; l\$LSa"
run_test

export COMMAND="export LS=\"s \$HOME\"; l\$LS"
run_test

export COMMAND="export tt=\"ho 123\"; ec\$tt"
run_test

export COMMAND="a=\$a:123; echo a > b123/123"
run_test

export COMMAND="a=\$a:123; echo a > \$a; rm \":123\""
run_test

export COMMAND="export a=\"a b\"; echo a > \$a"
run_test

export COMMAND="export a=\"'a'\"; echo \$a"
run_test

export COMMAND="export a='\"a\"'; echo \$a"
run_test

exit $RETURN_VALUE
