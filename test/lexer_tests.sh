#!/bin/bash

echo "NOTE: in DEBUG_LEXING mode, input past first complete line is ignored."

shopt -s nocasematch

RETURN_VALUE=0

export GREEN="\033[0;32m"
export RED="\033[0;31m"
export DEFAULT="\033[0m"

function ask_whether_section_should_be_run() {
  read -r -n 1 -p "Would you like to run $SECTION_NAME? [y/N] " SHOULD_RUN_SECTION
  echo
}

function run_test() {
  # Test file-based input
  echo "$COMMAND" \
      | ../calabash \
      |& cmp -s - <(echo -n "$EXPECTED_RESULT") \
    && echo -e "FILE:   [${GREEN}PASS${DEFAULT}] $COMMAND" \
    || { echo -e "FILE:   [${RED}FAIL${DEFAULT}] $COMMAND"; RETURN_VALUE=1; }
  # Test string-based input
  ../calabash -c "$COMMAND" \
      |& cmp -s - <(echo -n "$EXPECTED_RESULT") \
    && echo -e "STRING: [${GREEN}PASS${DEFAULT}] $COMMAND" \
    || { echo -e "STRING: [${RED}FAIL${DEFAULT}] $COMMAND"; RETURN_VALUE=1; }
}

export SECTION_NAME="EARLY INPUT TERMINATION TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="\\"
export EXPECTED_RESULT="\
Type: end of input | line index 0, char index 1
Context: \\
          ^^^
"
run_test

export COMMAND="'"
export EXPECTED_RESULT="\
../calabash: unclosed quote near line 1, char 1: '
                                                 ^
"
run_test

export COMMAND="\""
export EXPECTED_RESULT="\
../calabash: unclosed quote near line 1, char 1: \"
                                                 ^
"
run_test

export COMMAND="echo abc'def"
export EXPECTED_RESULT="\
../calabash: unclosed quote near line 1, char 9: ...o abc'def
                                                         ^
"
run_test

export COMMAND="ls a'bcd"
export EXPECTED_RESULT="\
../calabash: unclosed quote near line 1, char 5: ls a'bcd
                                                     ^
"
run_test

export COMMAND="echo a'bcdefg"
export EXPECTED_RESULT="\
../calabash: unclosed quote near line 1, char 7: ...cho a'bcdef...
                                                         ^
"
run_test

export COMMAND="calabash ab'cdefg"
export EXPECTED_RESULT="\
../calabash: unclosed quote near line 1, char 12: ...sh ab'cdefg
                                                          ^
"
run_test

export COMMAND="echo qwertyuiop'asdfghjkl"
export EXPECTED_RESULT="\
../calabash: unclosed quote near line 1, char 16: ...yuiop'asdfg...
                                                          ^
"
run_test

export COMMAND="echo qwertyuiop'asdfghjkl
zxcvbnm'mnb\"lkj
poiuytrewq"
export EXPECTED_RESULT="\
../calabash: unclosed quote near line 2, char 12: ...m'mnb\"lkj
                                                          ^
"
run_test

export COMMAND="abcdefg\\
hijklmn\"opq\\
rstu
vwxyz"
export EXPECTED_RESULT="\
../calabash: unclosed quote near line 2, char 8: ...jklmn\"opqrs...
                                                         ^
"
run_test

fi

exit $RETURN_VALUE
