#!/bin/bash

# Name : Hakim BOULAHYA
# Serial : 000391737
# Grade : INFO2

# Const. vars
readonly CONTENTPREFIX="--"
readonly INDENTATIONPREFIX="|"
readonly INDENTATIONSPACELENGTH=3
readonly EMPTY_ITEM="*"

echoIndentation(){
  echo -n $INDENTATIONPREFIX
  for ((i=0; i<$1; i++)); do
    printf '%*s' $INDENTATIONSPACELENGTH
    echo -n $INDENTATIONPREFIX  
  done
}
showContentPath(){
  if [ -z "$(ls)" ]; then echoIndentation $1; echo $CONTENTPREFIX $EMPTY_ITEM; fi # if empty
  ls|while read -r content; do # read all files/directories 
    # NOTE : the '-r' option allow to consider the backslash as a simple char
    if [ -L "$content" ]; then : # if link→do nothing
    elif [ -f "$content" ] || [ -d "$content" ]; then # if file or directory→echo name
      echoIndentation $1
      echo $CONTENTPREFIX $content
    if [ -d "$content" ]; then # browse it only if directory
      cd "$content" # Change current directory to browse the son 
      showContentPath $(($1+1))
      cd .. # get back to the father
    fi
    fi
  done
}

pwd # current directory
showContentPath 0 # Indentation level is the only parameter

exit 0
