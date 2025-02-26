#!/bin/bash

shopt -s nocasematch

export GREEN="\033[0;32m"
export RED="\033[0;31m"
export DEFAULT="\033[0m"

function ask_whether_section_should_be_run() {
  read -r -n 1 -p "Would you like to run $SECTION_NAME? [y/N] " SHOULD_RUN_SECTION
  echo
}

function run_test() {
  echo "$COMMAND" | ../calabash |& cmp - <(echo -n "$EXPECTED_RESULT") &>/dev/null && echo -e "[${GREEN}PASS${DEFAULT}] $COMMAND" || echo -e "[${RED}FAIL${DEFAULT}] $COMMAND"
}

export SECTION_NAME="SIMPLE COMMAND TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND=""
export EXPECTED_RESULT="\
(Empty tree)
"
run_test

export COMMAND="echo"
export EXPECTED_RESULT="\
Type simple command, arguments: echo
"
run_test

export COMMAND="echo \"hello\""
export EXPECTED_RESULT="\
Type simple command, arguments: echo, \"hello\"
"
run_test

export COMMAND="echo 'hello'"
export EXPECTED_RESULT="\
Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="echo 'hello world'"
export EXPECTED_RESULT="\
Type simple command, arguments: echo, 'hello world'
"
run_test

export COMMAND="ls > something.txt"
export EXPECTED_RESULT="\
Type simple command, arguments: ls, redirections: >something.txt
"
run_test

export COMMAND="ls 2 >& 1"
export EXPECTED_RESULT="\
Type simple command, arguments: ls, 2, redirections: >&1
"
run_test

export COMMAND="ls 2>&1"
export EXPECTED_RESULT="\
Type simple command, arguments: ls, redirections: 2>&1
"
run_test

export COMMAND="ls 2>&1 > something.txt"
export EXPECTED_RESULT="\
Type simple command, arguments: ls, redirections: 2>&1, >something.txt
"
run_test

export COMMAND="> something.txt ls"
export EXPECTED_RESULT="\
Type simple command, arguments: ls, redirections: >something.txt
"
run_test

export COMMAND="2>&1 > something.txt ls"
export EXPECTED_RESULT="\
Type simple command, arguments: ls, redirections: 2>&1, >something.txt
"
run_test

export COMMAND="2>&1 ls > something.txt"
export EXPECTED_RESULT="\
Type simple command, arguments: ls, redirections: 2>&1, >something.txt
"
run_test

export COMMAND="echo 'hello world' > something.txt"
export EXPECTED_RESULT="\
Type simple command, arguments: echo, 'hello world', redirections: >something.txt
"
run_test

export COMMAND="echo 'hello world' 2>&1"
export EXPECTED_RESULT="\
Type simple command, arguments: echo, 'hello world', redirections: 2>&1
"
run_test

export COMMAND="echo 'hello world' 2>&1 > something.txt"
export EXPECTED_RESULT="\
Type simple command, arguments: echo, 'hello world', redirections: 2>&1, >something.txt
"
run_test

export COMMAND="A=B echo 'hello world'"
export EXPECTED_RESULT="\
Type simple command, assignments: A=B, arguments: echo, 'hello world'
"
run_test

export COMMAND="echo 'hello world' A=B"
export EXPECTED_RESULT="\
Type simple command, arguments: echo, 'hello world', A=B
"
run_test

export COMMAND="A=B echo C=D 'hello world' E=F"
export EXPECTED_RESULT="\
Type simple command, assignments: A=B, arguments: echo, C=D, 'hello world', E=F
"
run_test

export COMMAND="> a.txt A=B > b.txt echo 2>&1 C=D > c.txt 'hello world' > d.txt E=F > e.txt"
export EXPECTED_RESULT="\
Type simple command, assignments: A=B, arguments: echo, C=D, 'hello world', E=F, redirections: >a.txt, >b.txt, 2>&1, >c.txt, >d.txt, >e.txt
"
run_test

fi

export SECTION_NAME="PIPE/PIPE BOTH TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="echo 'hello' | wc -c"
export EXPECTED_RESULT="\
Type pipe
  -> Type simple command, arguments: echo, 'hello'
  -> Type simple command, arguments: wc, -c
"
run_test

export COMMAND="echo 'hello' | wc -c | tr -d ' '"
export EXPECTED_RESULT="\
Type pipe
  -> Type pipe
    -> Type simple command, arguments: echo, 'hello'
    -> Type simple command, arguments: wc, -c
  -> Type simple command, arguments: tr, -d, ' '
"
run_test

export COMMAND="echo 'hello' | wc -c | tr -d ' ' | cat"
export EXPECTED_RESULT="\
Type pipe
  -> Type pipe
    -> Type pipe
      -> Type simple command, arguments: echo, 'hello'
      -> Type simple command, arguments: wc, -c
    -> Type simple command, arguments: tr, -d, ' '
  -> Type simple command, arguments: cat
"
run_test

export COMMAND="ls |& cat"
export EXPECTED_RESULT="\
Type pipe both
  -> Type simple command, arguments: ls
  -> Type simple command, arguments: cat
"
run_test

export COMMAND="ls 2>/dev/null | grep -C 10 'a'"
export EXPECTED_RESULT="\
Type pipe
  -> Type simple command, arguments: ls, redirections: 2>/dev/null
  -> Type simple command, arguments: grep, -C, 10, 'a'
"
run_test

fi

export SECTION_NAME="NEGATION TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="! ls"
export EXPECTED_RESULT="\
Type negation
  -> Type simple command, arguments: ls
"
run_test

export COMMAND="! ! ls"
export EXPECTED_RESULT="\
Type negation
  -> Type negation
    -> Type simple command, arguments: ls
"
run_test

export COMMAND="! echo 'hello'"
export EXPECTED_RESULT="\
Type negation
  -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="! ls 2>/dev/null | grep -C 10 'a'"
export EXPECTED_RESULT="\
Type negation
  -> Type pipe
    -> Type simple command, arguments: ls, redirections: 2>/dev/null
    -> Type simple command, arguments: grep, -C, 10, 'a'
"
run_test

fi

export SECTION_NAME="AND/OR TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="echo 'hello' && echo 'hi'"
export EXPECTED_RESULT="\
Type and
  -> Type simple command, arguments: echo, 'hello'
  -> Type simple command, arguments: echo, 'hi'
"
run_test

export COMMAND="echo 'hello' && echo 'hi' && echo 'hey'"
export EXPECTED_RESULT="\
Type and
  -> Type and
    -> Type simple command, arguments: echo, 'hello'
    -> Type simple command, arguments: echo, 'hi'
  -> Type simple command, arguments: echo, 'hey'
"
run_test

export COMMAND="cmp a.txt b.txt && echo 'Success' || echo 'Failure'"
export EXPECTED_RESULT="\
Type or
  -> Type and
    -> Type simple command, arguments: cmp, a.txt, b.txt
    -> Type simple command, arguments: echo, 'Success'
  -> Type simple command, arguments: echo, 'Failure'
"
run_test

export COMMAND="ls -1 | grep -C 10 'a' | grep 'b' && ls -1 | grep -C 10 'b' | grep 'a'"
export EXPECTED_RESULT="\
Type and
  -> Type pipe
    -> Type pipe
      -> Type simple command, arguments: ls, -1
      -> Type simple command, arguments: grep, -C, 10, 'a'
    -> Type simple command, arguments: grep, 'b'
  -> Type pipe
    -> Type pipe
      -> Type simple command, arguments: ls, -1
      -> Type simple command, arguments: grep, -C, 10, 'b'
    -> Type simple command, arguments: grep, 'a'
"
run_test

export COMMAND="! echo 'hello' && echo 'Success' || echo 'Failure'"
export EXPECTED_RESULT="\
Type or
  -> Type and
    -> Type negation
      -> Type simple command, arguments: echo, 'hello'
    -> Type simple command, arguments: echo, 'Success'
  -> Type simple command, arguments: echo, 'Failure'
"
run_test

export COMMAND="! echo 'hello' && echo 'Success' | wc -c || echo 'Failure' | wc -c"
export EXPECTED_RESULT="\
Type or
  -> Type and
    -> Type negation
      -> Type simple command, arguments: echo, 'hello'
    -> Type pipe
      -> Type simple command, arguments: echo, 'Success'
      -> Type simple command, arguments: wc, -c
  -> Type pipe
    -> Type simple command, arguments: echo, 'Failure'
    -> Type simple command, arguments: wc, -c
"
run_test

fi

export SECTION_NAME="SEQUENCE/BACKGROUND TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="echo 'hello' ;"
export EXPECTED_RESULT="\
Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="echo 'hello' ; ls"
export EXPECTED_RESULT="\
Type sequence
  -> Type simple command, arguments: echo, 'hello'
  -> Type simple command, arguments: ls
"
run_test

export COMMAND="echo 'hello' ; ls ; cat a.txt"
export EXPECTED_RESULT="\
Type sequence
  -> Type sequence
    -> Type simple command, arguments: echo, 'hello'
    -> Type simple command, arguments: ls
  -> Type simple command, arguments: cat, a.txt
"
run_test

export COMMAND="echo 'hello' &"
export EXPECTED_RESULT="\
Type background
  -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="echo 'hello' & ls"
export EXPECTED_RESULT="\
Type sequence
  -> Type background
    -> Type simple command, arguments: echo, 'hello'
  -> Type simple command, arguments: ls
"
run_test

export COMMAND="echo 'hello' & ls & cat a.txt"
export EXPECTED_RESULT="\
Type sequence
  -> Type sequence
    -> Type background
      -> Type simple command, arguments: echo, 'hello'
    -> Type background
      -> Type simple command, arguments: ls
  -> Type simple command, arguments: cat, a.txt
"
run_test

export COMMAND="echo 'hello' ; ls & cat a.txt"
export EXPECTED_RESULT="\
Type sequence
  -> Type sequence
    -> Type simple command, arguments: echo, 'hello'
    -> Type background
      -> Type simple command, arguments: ls
  -> Type simple command, arguments: cat, a.txt
"
run_test

export COMMAND="echo 'hello' ; ls & cat a.txt &"
export EXPECTED_RESULT="\
Type sequence
  -> Type sequence
    -> Type simple command, arguments: echo, 'hello'
    -> Type background
      -> Type simple command, arguments: ls
  -> Type background
    -> Type simple command, arguments: cat, a.txt
"
run_test

export COMMAND="echo 'hello' & ls ; cat a.txt"
export EXPECTED_RESULT="\
Type sequence
  -> Type sequence
    -> Type background
      -> Type simple command, arguments: echo, 'hello'
    -> Type simple command, arguments: ls
  -> Type simple command, arguments: cat, a.txt
"
run_test

export COMMAND="echo 'hello' & ls ; cat a.txt &"
export EXPECTED_RESULT="\
Type sequence
  -> Type sequence
    -> Type background
      -> Type simple command, arguments: echo, 'hello'
    -> Type simple command, arguments: ls
  -> Type background
    -> Type simple command, arguments: cat, a.txt
"
run_test

export COMMAND="cat a.txt ; echo 'hello' && ls & ! cat b.txt | cat c.txt ;"
export EXPECTED_RESULT="\
Type sequence
  -> Type sequence
    -> Type simple command, arguments: cat, a.txt
    -> Type background
      -> Type and
        -> Type simple command, arguments: echo, 'hello'
        -> Type simple command, arguments: ls
  -> Type negation
    -> Type pipe
      -> Type simple command, arguments: cat, b.txt
      -> Type simple command, arguments: cat, c.txt
"
run_test

export COMMAND="cat a.txt & echo 'hello' && ls ; ! cat b.txt | cat c.txt ;"
export EXPECTED_RESULT="\
Type sequence
  -> Type sequence
    -> Type background
      -> Type simple command, arguments: cat, a.txt
    -> Type and
      -> Type simple command, arguments: echo, 'hello'
      -> Type simple command, arguments: ls
  -> Type negation
    -> Type pipe
      -> Type simple command, arguments: cat, b.txt
      -> Type simple command, arguments: cat, c.txt
"
run_test

fi

export SECTION_NAME="SUBSHELL/GROUP TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="( ls )"
export EXPECTED_RESULT="\
Type subshell
  -> Type simple command, arguments: ls
"
run_test

export COMMAND="( ls ; )"
export EXPECTED_RESULT="\
Type subshell
  -> Type simple command, arguments: ls
"
run_test

export COMMAND="{ ls ; }"
export EXPECTED_RESULT="\
Type group
  -> Type simple command, arguments: ls
"
run_test

export COMMAND="{ echo 'hello world' > something.txt ; }"
export EXPECTED_RESULT="\
Type group
  -> Type simple command, arguments: echo, 'hello world', redirections: >something.txt
"
run_test

export COMMAND="{ ls ; } && ( echo 'hello' )"
export EXPECTED_RESULT="\
Type and
  -> Type group
    -> Type simple command, arguments: ls
  -> Type subshell
    -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="( ls && echo 'hello' )"
export EXPECTED_RESULT="\
Type subshell
  -> Type and
    -> Type simple command, arguments: ls
    -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="{ ls && echo 'hello' ; }"
export EXPECTED_RESULT="\
Type group
  -> Type and
    -> Type simple command, arguments: ls
    -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="( { ls && echo 'hello' ; } 2>&1 ) > something.txt"
export EXPECTED_RESULT="\
Type subshell, redirections: >something.txt
  -> Type group, redirections: 2>&1
    -> Type and
      -> Type simple command, arguments: ls
      -> Type simple command, arguments: echo, 'hello'
"
run_test

fi

export SECTION_NAME="FUNCTION TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="function hello() { echo 'hello' ; }"
export EXPECTED_RESULT="\
Type function, identifier: hello
  -> Type group
    -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="function hello { echo 'hello' ; }"
export EXPECTED_RESULT="\
Type function, identifier: hello
  -> Type group
    -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="hello() { echo 'hello' ; }"
export EXPECTED_RESULT="\
Type function, identifier: hello
  -> Type group
    -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="hello() { echo 'hello' ; } ; hello"
export EXPECTED_RESULT="\
Type sequence
  -> Type function, identifier: hello
    -> Type group
      -> Type simple command, arguments: echo, 'hello'
  -> Type simple command, arguments: hello
"
run_test

export COMMAND="function hello({ echo 'hello' ; })"
export EXPECTED_RESULT="\
Type function, identifier: hello
  -> Type subshell
    -> Type group
      -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="function hello() ({ echo 'hello' ; })"
export EXPECTED_RESULT="\
Type function, identifier: hello
  -> Type subshell
    -> Type group
      -> Type simple command, arguments: echo, 'hello'
"
run_test

fi

export SECTION_NAME="WHILE/UNTIL COMMAND TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="while true ; do echo 'hello' ; done"
export EXPECTED_RESULT="\
Type while
  -> Type simple command, arguments: true
  -> Type group
    -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="until false ; do ls ; done"
export EXPECTED_RESULT="\
Type until
  -> Type simple command, arguments: false
  -> Type group
    -> Type simple command, arguments: ls
"
run_test

export COMMAND="while true ; do something ; something else ; done"
export EXPECTED_RESULT="\
Type while
  -> Type simple command, arguments: true
  -> Type group
    -> Type sequence
      -> Type simple command, arguments: something
      -> Type simple command, arguments: something, else
"
run_test

export COMMAND="S=w ; while [ \$S != www ] ; do echo \$S ; S=w\$S ; done"
export EXPECTED_RESULT="\
Type sequence
  -> Type simple command, assignments: S=w
  -> Type while
    -> Type simple command, arguments: [, \$S, !=, www, ]
    -> Type group
      -> Type sequence
        -> Type simple command, arguments: echo, \$S
        -> Type simple command, assignments: S=w\$S
"
run_test

export COMMAND="while true ; do until false ; do echo hello ; done ; done"
export EXPECTED_RESULT="\
Type while
  -> Type simple command, arguments: true
  -> Type group
    -> Type until
      -> Type simple command, arguments: false
      -> Type group
        -> Type simple command, arguments: echo, hello
"
run_test

fi

export SECTION_NAME="MULTILINE TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="{
  ls
}"
export EXPECTED_RESULT="\
Type group
  -> Type simple command, arguments: ls
"
run_test

export COMMAND="{ ls }
}"
export EXPECTED_RESULT="\
Type group
  -> Type simple command, arguments: ls, }
"
run_test

export COMMAND="function hello() {
  echo 'hello'
}"
export EXPECTED_RESULT="\
Type function, identifier: hello
  -> Type group
    -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="echo a &&
echo b"
export EXPECTED_RESULT="\
Type and
  -> Type simple command, arguments: echo, a
  -> Type simple command, arguments: echo, b
"
run_test

export COMMAND="echo \\
'hello'"
export EXPECTED_RESULT="\
Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="echo 'hello' \\
&"
export EXPECTED_RESULT="\
Type background
  -> Type simple command, arguments: echo, 'hello'
"
run_test

export COMMAND="echo 'hello' && echo \\
'world'"
export EXPECTED_RESULT="\
Type and
  -> Type simple command, arguments: echo, 'hello'
  -> Type simple command, arguments: echo, 'world'
"
run_test

export COMMAND="echo \"hello\" && echo \"wo\\
rld\""
export EXPECTED_RESULT="\
Type and
  -> Type simple command, arguments: echo, \"hello\"
  -> Type simple command, arguments: echo, \"world\"
"
run_test

export COMMAND="echo 'hello' && echo 'wo\\
rld'"
export EXPECTED_RESULT="\
Type and
  -> Type simple command, arguments: echo, 'hello'
  -> Type simple command, arguments: echo, 'wo\\
rld'
"
run_test

fi

export SECTION_NAME="SYNTAX ERROR TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="{ ls )"
export EXPECTED_RESULT="\
../calabash: syntax error near line 1, char 6: { ls )
                                                    ^
"
run_test

export COMMAND="echo &&& ls"
export EXPECTED_RESULT="\
../calabash: syntax error near line 1, char 8: ...ho &&& ls
                                                       ^
"
run_test

export COMMAND="echo &&&&& ls"
export EXPECTED_RESULT="\
../calabash: syntax error near line 1, char 8: ...ho &&&&& ls
                                                       ^^
"
run_test

export COMMAND="else"
export EXPECTED_RESULT="\
../calabash: syntax error near line 1, char 1: else
                                               ^^^^
"
run_test

export COMMAND="something() (else)"
export EXPECTED_RESULT="\
../calabash: syntax error near line 1, char 14: ...g() (else)
                                                        ^^^^
"
run_test

export COMMAND="function blah() {blahblahblah"
export EXPECTED_RESULT="\
../calabash: syntax error near line 1, char 17: ...ah() {blahblahb...
                                                        ^^^^^^^^^^
"
run_test

export COMMAND="echo hello () echo hello"
export EXPECTED_RESULT="\
../calabash: syntax error near line 1, char 12: ...ello () ech...
                                                        ^
"
run_test

export COMMAND="() echo hello"
export EXPECTED_RESULT="\
../calabash: syntax error near line 1, char 2: () echo...
                                                ^
"
run_test

export COMMAND="echo hello | | for WORD in dog cat pig; do echo \$WORD ; done"
export EXPECTED_RESULT="\
../calabash: syntax error near line 1, char 14: ...lo | | for ...
                                                        ^
"
run_test

fi

export SECTION_NAME="UNSUPPORTED FEATURE TESTS"
ask_whether_section_should_be_run

if [[ $SHOULD_RUN_SECTION == "y" ]]; then

export COMMAND="for WORD in dog cat pig; do echo \$WORD ; done"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 1: for WORD...
                                                      ^^^
"
run_test

export COMMAND="for WORD in dog cat pig; do echo \$WORD | | ; done"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 1: for WORD...
                                                      ^^^
"
run_test

export COMMAND="! [[ something ]]"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 3: ! [[ some...
                                                        ^^
"
run_test

export COMMAND="function hello() for WORD in dog cat pig; do echo \$WORD ; done"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 18: ...lo() for WORD...
                                                               ^^^
"
run_test

export COMMAND="function hello() {
  for WORD in dog cat pig; do echo \$WORD ; done
}"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 2, char 3:   for WORD...
                                                        ^^^
"
run_test

export COMMAND="time ls"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 1: time ls
                                                      ^^^^
"
run_test

export COMMAND="time echo 'hello'"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 1: time echo...
                                                      ^^^^
"
run_test

export COMMAND="! time ls"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 3: ! time ls
                                                        ^^^^
"
run_test

export COMMAND="! ! time ! ls"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 5: ! ! time ! ls
                                                          ^^^^
"
run_test

export COMMAND="time echo 'hello' | wc -c | tr -d ' '"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 1: time echo...
                                                      ^^^^
"
run_test

export COMMAND="coproc MY_COPROC { ls; }"
export EXPECTED_RESULT="\
../calabash: unsupported feature near line 1, char 1: coproc MY_C...
                                                      ^^^^^^
"
run_test

fi
