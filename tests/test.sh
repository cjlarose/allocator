#!/usr/bin/env bash
#==============================================================================
# Author: Cody Mingus
# File: test.sh
#
# Purpose: Test the my_malloc libraries by invoking several client programs
# and checking their return status. It is assumed that the source code for
# those programs are located in this directory, and that the file name starts
# with a number, followed by an underscore, then "test" and ends with ".c"
# Like this: [0-9][0-9]_test*.c
#==============================================================================

# Constants
DIRS=`ls tests`
CODE_DIR=`pwd`
TEST_DIR=$CODE_DIR/tests
TOTAL_TESTS=`find . -name "[0-9][0-9]_test*.c" | wc -l`
PROGRESS="python $TEST_DIR/progress.py"
TEMP_FILE=`mktemp`

# Variables
test_number=0

# Functions
function warn {
    echo -en "\e[0;93m" # YELLOW
    echo $1
    tput sgr0
}

function good {
    echo -en "\e[0;92m" # GREEN
    echo $1
    tput sgr0
}

function err {
    echo -en "\e[0;91m" # RED
    echo $1
    tput sgr0
}

function progress {
    echo -en "`$PROGRESS $@`\r"
}

function finish {
    rm $TEMP_FILE
}
trap finish EXIT

# Take a quick look at the tests to see if they look okay...
for dir in $DIRS; do

    # Try to move into a sub directory
    if [ ! -d tests/$dir ]; then
        continue
    fi
    pushd tests/$dir &> /dev/null
    if [ $? -ne 0 ]; then
        continue
    fi
    files=`ls [0-9][0-9]_test*.c`

    # Look at each file
    for file in $files; do
        warnings=`grep "malloc(.*)" $file | wc -l`
        if [ $warnings -ne 0 ]; then
            warn "Warning. $file contains a call to malloc. Did you mean to use myMalloc?"
        fi
        warnings=`grep "free(.*)" $file | wc -l`
        if [ $warnings -ne 0 ]; then
            warn "Warning. $file contains a call to free. Did you mean to use myFree?"
        fi
    done

    popd &> /dev/null
done

# Run each test
for dir in $DIRS; do

    if [ ! -d tests/$dir ]; then
        continue
    fi
    pushd tests/$dir &> /dev/null
    if [ $? -ne 0 ]; then
        continue
    fi
    files=`ls [0-9][0-9]_test*.c`
    lib=`cat lib.txt`

    for file in $files; do

        test_number=$(($test_number + 1))
        progress $test_number $TOTAL_TESTS

        if [ $# -gt 0 ]; then
            if [ $test_number -le $1 ]; then
                continue
            fi
        fi

        # Compile the test
        gcc -O2 $file -L$CODE_DIR $lib -lpthread -lstdc++ &> $TEMP_FILE
        if [ $? -ne 0 ]; then
            err "Failed to compile $file. Rage quitting..."
            cat $TEMP_FILE
            exit 1
        fi

        # Run the test
        ./a.out &> $TEMP_FILE
        if [ $? -ne 0 ]; then
            echo "Failed: $file"
            cat $TEMP_FILE
            exit 1
        fi

        # Ensure no memory errors with valgrind
        valgrind --error-exitcode=-42 ./a.out &> /dev/null
        if [ $? -ne 0 ]; then
            err "valgrind detected errors when running $file"
            exit 1
        fi


    done

    popd &> /dev/null
done

progress
echo ''
good "All tests passed :)"
