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

export SECTION_NAME="WORD TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND=""
export EXPECTED_RESULT="\
Type: end of input | line index 0, char index 0
Context: 
         ^^^
"
run_test

export COMMAND="a"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`a\`
Context: a
         ^
Type: end of input | line index 0, char index 1
Context: a
          ^^^
"
run_test

export COMMAND="abc"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`abc\`
Context: abc
         ^^^
Type: end of input | line index 0, char index 3
Context: abc
            ^^^
"
run_test

export COMMAND="abcdefghijklm"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`abcdefghijklm\`
Context: abcdefghij...
         ^^^^^^^^^^
Type: end of input | line index 0, char index 13
Context: ...ijklm
                 ^^^
"
run_test

export COMMAND="abc'def'ghi"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`abc'def'ghi\`
Context: abc'def'gh...
         ^^^^^^^^^^
Type: end of input | line index 0, char index 11
Context: ...f'ghi
                 ^^^
"
run_test

export COMMAND="\"abc def ghi\""
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`\"abc def ghi\"\`
Context: \"abc def g...
         ^^^^^^^^^^
Type: end of input | line index 0, char index 13
Context: ... ghi\"
                 ^^^
"
run_test

export COMMAND="'abc
def
ghi'"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`'abc
def
ghi'\`
Context: 'abc...
         ^^^^
Type: end of input | line index 2, char index 4
Context: ghi'
             ^^^
"
run_test

export COMMAND="abc\\
def\\
ghi"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`abcdefghi\`
Context: abcdefghi
         ^^^^^^^^^
Type: end of input | line index 2, char index 3
Context: ghi
            ^^^
"
run_test

export COMMAND="abc\\ def\\ ghi"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`abc\\ def\\ ghi\`
Context: abc\\ def\\ ...
         ^^^^^^^^^^
Type: end of input | line index 0, char index 13
Context: ...\\ ghi
                 ^^^
"
run_test

fi

export SECTION_NAME="WHITESPACE TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND=" "
export EXPECTED_RESULT="\
Type: whitespace   | line index 0, char index 0
Context:  
         ^
Type: end of input | line index 0, char index 1
Context:  
          ^^^
"
run_test

export COMMAND="   "
export EXPECTED_RESULT="\
Type: whitespace   | line index 0, char index 0
Context:    
         ^^^
Type: end of input | line index 0, char index 3
Context:    
            ^^^
"
run_test

export COMMAND=" abc"
export EXPECTED_RESULT="\
Type: whitespace   | line index 0, char index 0
Context:  abc
         ^
Type: word         | line index 0, char index 1
Word content: \`abc\`
Context:  abc
          ^^^
Type: end of input | line index 0, char index 4
Context:  abc
             ^^^
"
run_test

export COMMAND="def "
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`def\`
Context: def 
         ^^^
Type: whitespace   | line index 0, char index 3
Context: def 
            ^
Type: end of input | line index 0, char index 4
Context: def 
             ^^^
"
run_test

export COMMAND=" ghi "
export EXPECTED_RESULT="\
Type: whitespace   | line index 0, char index 0
Context:  ghi 
         ^
Type: word         | line index 0, char index 1
Word content: \`ghi\`
Context:  ghi 
          ^^^
Type: whitespace   | line index 0, char index 4
Context:  ghi 
             ^
Type: end of input | line index 0, char index 5
Context:  ghi 
              ^^^
"
run_test

export COMMAND="abc def ghi"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`abc\`
Context: abc def ...
         ^^^
Type: whitespace   | line index 0, char index 3
Context: abc def g...
            ^
Type: word         | line index 0, char index 4
Word content: \`def\`
Context: abc def ghi
             ^^^
Type: whitespace   | line index 0, char index 7
Context: ...c def ghi
                 ^
Type: word         | line index 0, char index 8
Word content: \`ghi\`
Context: ... def ghi
                 ^^^
Type: end of input | line index 0, char index 11
Context: ...f ghi
                 ^^^
"
run_test

fi

export SECTION_NAME="OPERATOR TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="&&"
export EXPECTED_RESULT="\
Type: operator     | line index 0, char index 0
Operator content: \`&&\`
Context: &&
         ^^
Type: end of input | line index 0, char index 2
Context: &&
           ^^^
"
run_test

export COMMAND="&&&&&"
export EXPECTED_RESULT="\
Type: operator     | line index 0, char index 0
Operator content: \`&&\`
Context: &&&&&
         ^^
Type: operator     | line index 0, char index 2
Operator content: \`&&\`
Context: &&&&&
           ^^
Type: operator     | line index 0, char index 4
Operator content: \`&\`
Context: &&&&&
             ^
Type: end of input | line index 0, char index 5
Context: &&&&&
              ^^^
"
run_test

export COMMAND="a||b"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`a\`
Context: a||b
         ^
Type: operator     | line index 0, char index 1
Operator content: \`||\`
Context: a||b
          ^^
Type: word         | line index 0, char index 3
Word content: \`b\`
Context: a||b
            ^
Type: end of input | line index 0, char index 4
Context: a||b
             ^^^
"
run_test

export COMMAND="a || b"
export EXPECTED_RESULT="\
Type: word         | line index 0, char index 0
Word content: \`a\`
Context: a || b
         ^
Type: whitespace   | line index 0, char index 1
Context: a || b
          ^
Type: operator     | line index 0, char index 2
Operator content: \`||\`
Context: a || b
           ^^
Type: whitespace   | line index 0, char index 4
Context: a || b
             ^
Type: word         | line index 0, char index 5
Word content: \`b\`
Context: a || b
              ^
Type: end of input | line index 0, char index 6
Context: ... || b
                 ^^^
"
run_test

export COMMAND="&;|()<>"
export EXPECTED_RESULT="\
Type: operator     | line index 0, char index 0
Operator content: \`&\`
Context: &;|()<...
         ^
Type: operator     | line index 0, char index 1
Operator content: \`;\`
Context: &;|()<>
          ^
Type: operator     | line index 0, char index 2
Operator content: \`|\`
Context: &;|()<>
           ^
Type: operator     | line index 0, char index 3
Operator content: \`(\`
Context: &;|()<>
            ^
Type: operator     | line index 0, char index 4
Operator content: \`)\`
Context: &;|()<>
             ^
Type: operator     | line index 0, char index 5
Operator content: \`<>\`
Context: &;|()<>
              ^^
Type: end of input | line index 0, char index 7
Context: ...|()<>
                 ^^^
"
run_test

fi

export SECTION_NAME="UNSUPPORTED FEATURE TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="\$(( a = 1 + 2 ))"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 1: \$(( a = ...
                                                      ^^^
"
run_test

export COMMAND="echo \$(echo a)"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 6: echo \$(echo ...
                                                           ^^
"
run_test

export COMMAND="cat <(ls a) <(ls b)"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 5: cat <(ls a)...
                                                          ^^
"
run_test

export COMMAND="dunno know how to use >() yet"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 23: ... use >() yet
                                                               ^^
"
run_test

export COMMAND="MY_FILE=\`mktemp\`"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 9: ...FILE=\`mktem...
                                                              ^
"
run_test

fi

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
