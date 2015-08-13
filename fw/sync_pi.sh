#!/bin/bash

# Colorful message formatting
UPDATES="\033[1;33m==>\033[39m %s\033[0m\r";
MESSAGE="\033[1;32m==>\033[39m %s\033[0m\n";
PROBLEM="\033[1;31m==>\033[39m %s\033[0m\n";

# Catch interruption signal
trap '{ printf "\n$MESSAGE" "Exiting!"; exit; }' INT;

# Check if source location passed
if [ -z "$1" ];
then
    printf "$PROBLEM" "'source' (1st) argument is missing";
    exit 1;
fi;

# Check if destination location passed
if [ -z "$2" ];
then
    printf "$PROBLEM" "'destination' (2nd) argument is missing";
    exit 1;
fi;

# Check if interval is specified
if [ -z "$3" ];
then
    interval=3;
else
    interval=$3;
fi;

# Set global states
old_checksum="0";
new_checksum="$(tar c $1 | md5sum)";

# Enter "daemon" loop
while true;
do
    if [ "$old_checksum" != "$new_checksum" ];
    then
        printf "$MESSAGE" "[$(date +%k:%M:%S)] Synchronizing $1 to $2";
        rsync --progress                 \
              --recursive                \
              --archive                  \
              --checksum                 \
              --delete                   \
              --exclude main             \
              --exclude build            \
              --exclude .sconsign.dblite \
              $1                         \
              $2;
        old_checksum=$new_checksum;
    fi;
    # Update checksum
    new_checksum="$(tar c $1 | md5sum)";
    # Feedback for the user
    printf "$UPDATES" "[$(date +%k:%M:%S)] Looking for changes...";
    # Pause
    $(sleep $interval);
done;
