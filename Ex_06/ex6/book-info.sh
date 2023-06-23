#!/bin/bash


if [ ! -f $1 ]
then
    echo "File $1 not found"
    exit

fi

sort $1 | sed -n '5{h; d;}; 9{ p; x ;}; p' > sort.txt

while [[ $input != "quit" ]] ; do
    while read -r line ; do
        if [ ! -f $line ] ; then
            echo "File $line not found"
            exit
        fi

    done < sort.txt

    echo "Enter: number / files / names / stats <chapter-name> / search <word>/ quit"

    read input

    if [[ ! $input ]] ; then
        exit
    fi

    if [[ $input == "number" ]] ; then
        sed -n '$=' $1 | sed 's/$/ chapters/g'
    fi

    prefix=1

    if [[ $1 == "file_list2.txt" ]] ; then
        prefix=2
    fi

    if [[ $input == "files" ]] ; then
        while read -r line ; do
            printf -v j "%02d" $((prefix++))
            echo "Chapter-$j: $line"

        done < sort.txt > prefixsort.txt

        cat prefixsort.txt

    fi

    if [[ $input == "names" ]] ; then
        while read -r line ; do
            printf -v j "%02d" $((prefix++))
            chapter=$line
            echo "Chapter-$j: `head -n3 $chapter | tail -n 1`"

        done < sort.txt > prefixChap.txt

        cat prefixChap.txt

    fi

    declare -a array=($input)

    if [[ ${array[0]} == "stats" ]] ; then
        if [[ ${#array[@]} > 1 && $(grep -e ${array[1]} prefixChap.txt) ]] ; then
            TITLE=$(grep ${array[1]} prefixChap.txt | cut -d ' ' -f 2,3,4)
            CHAP=$(grep ${array[1]} prefixsort.txt | cut -d ' ' -f 2)
            CHAP2=$(grep ${array[1]} prefixsort.txt | cut -d ':' -f 1)
            LINES=$(tail -n +3 $CHAP | grep -v $CHAP2 | wc -l | sed -e 's/[\t ]//g;/^$/d')
            WORDS=$(tail -n +3 $CHAP | grep -v $CHAP2 | wc -w | sed -e 's/[\t ]//g;/^$/d')
            echo "$CHAP2: $LINES lines, $WORDS words"

        elif [[ ${#array[@]} = 1 ]] ; then
            while read -r line ; do
                declare -a array2=($line)
                TITLE=$(grep ${array2[1]} prefixChap.txt | cut -d ' ' -f 2,3,4)
                CHAP=$(grep ${array2[1]} prefixsort.txt | cut -d ' ' -f 2)
                CHAP2=$(grep ${array2[1]} prefixsort.txt | cut -d ':' -f 1)
                LINES=$(tail -n +3 $CHAP | grep -v $CHAP2 | wc -l | sed -e 's/[\t ]//g;/^$/d')
                WORDS=$(tail -n +3 $CHAP | grep -v $CHAP2 | wc -w | sed -e 's/[\t ]//g;/^$/d')
                echo "$CHAP2: $LINES lines, $WORDS words"

            done < prefixsort.txt

        fi

    fi

    if [[ ${array[0]} == "search" ]] ; then
        if [[ ${#array[@]} > 1 ]] ; then
            while read -r line ; do
                declare -a array2=($line)
                CHAP=$(grep ${array2[1]} prefixsort.txt | cut -d ' ' -f 2)
                CHAP2=$(grep ${array2[1]} prefixsort.txt | cut -d ':' -f 1)
                CNT=$(egrep -o -i -w ${array[1]} $CHAP | wc -l)

                if [[ $CNT -ne 0 ]] ; then
                    echo $CHAP2: $CNT
                fi

            done < prefixsort.txt
        fi
    fi

done
