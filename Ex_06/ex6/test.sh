#!/bin/bash
# Created by Shlomo Hoory

# Assumes for each i in 1 ... $LAST the following files exists (or not depending on test):
# - file_list$i - file list file for test $i
# - input$x.txt - input (stdin) for the book-info.sh script
# - expected_output$x.txt - output (stdout) for the script
#
# stderr of script is not caught and not tested.
#
# generate output files using the following command:
# for i in 1 2 3 4 5; do ./book-info.sh file_list$i.txt < input$i.txt > expected_output$i.txt; done 

LAST=5

i=1
while [[ $i -le $LAST ]]; do
  ./book-info.sh file_list$i.txt < input$i.txt > actual_output$i.txt
  if [[ $(diff actual_output$i.txt expected_output$i.txt|wc -l) -gt 0 ]]; then
    echo Test $i failed
  else
    echo Test $i passed
  fi
  i=$((i+1))
done
