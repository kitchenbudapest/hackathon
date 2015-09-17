#!/bin/bash

# Draw a 80 columns length line
decorate()
{
    for ((i=1; i<=80; i++));
    do
        printf "-";
    done;
    printf "\n";
}


# If no arguments passed
if [ -z "$1" ];
then
    printf "Missing executable (first argument)\n";
# If at least one argument passed
else
    reset;
    scons;
    decorate;
    commands="reset && scons &&";
    # If testing
    if [ "$1" == "-t" ] || [ "$1" == "--test" ];
    then
        # If second argument is missing
        if [ -z "$2" ];
        then
            printf "Missing executable (second argument)\n";
        # If there is a second argument
        else
            printf "==> $commands valgrind --track-origins=yes"
            printf                       " --leak-check=full"
            printf                       " ./$2\n";
            decorate;
            valgrind --track-origins=yes \
                     --leak-check=full   \
                     ./$2;
        fi;
    # If running
    else
        printf "==> $commands ./$1\n";
        decorate;
        ./$1;
    fi;
fi;

# Terminate program
exit;
