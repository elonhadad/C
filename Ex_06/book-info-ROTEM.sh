#!/bin/bash
#Student1: Rotem Elimelech, ID: 313284606
#Student2: Elon Hadad, ID: 034672139


if [[ ! -f $1 ]] ; then
  echo "File $1 not found"
  exit
fi

file=$1

while read -r chapter ; do
    if [[ ! -f $chapter ]] ; then
     echo "File $chapter not found"
     exit
    fi
done < $file

echo "Enter: number / files / names / stats <chapter-name> / search <word>/ quit"

while read line; do


    if [[ $line == "quit" ]]; then
      break
    fi
    
    if [[ $line == "number" ]] ; then
        #grep moby-CHAPTER $file | wc -l | sed 's/$/ chapters/g'
        n=0
        while read -r chapter ; do
          if [[ -f $chapter ]] ; then
            n=$((n+1))
          fi
        done < $file
        echo $n chapters
    fi
    
    if [[ $line == "files" ]] ; then
        while read -r chapter ; do
          prefix=$(head -n1 $chapter | sed 's/$/:/g')
          echo "$prefix $chapter" >> chapters.txt
        done < $file
        
        sort chapters.txt
        rm chapters.txt
    fi
    
    if [[ $line == "names" ]] ; then
        while read -r chapter ; do
          prefix=$(head -n1 $chapter | sed 's/$/:/g')
          name=$(head -n3 $chapter | tail -n1)
          echo "$prefix $name" >> chapterNames.txt
        done < $file
        if [[ -f chapterNames.txt ]] ; then
          sort chapterNames.txt
          rm chapterNames.txt
        fi
    fi
    
    if [[ $line =~ ^"stats"  ]] ; then
      while read -r chapter ; do
        prefix=$(head -n1 $chapter | sed 's/$/:/g')
        linesStats=$(sed -n '1,2!p' $chapter | wc -l | sed 's/$/ lines,/g')
        wordsStats=$(sed -n '1,2!p' $chapter | wc -w | sed 's/$/ words/g')
        echo "$prefix $linesStats $wordsStats" >> chapterStats.txt
      done < $file
    
      if [[ $line == "stats" ]] ; then
        if [[ -f chapterStats.txt ]] ; then
          sort chapterStats.txt
          rm chapterStats.txt
        fi
        
      else
        if [[ -f chapterStats.txt ]] ; then
          search=$(echo $line | sed 's/stats//g')
          grep $search chapterStats.txt
          rm chapterStats.txt
        fi
      fi
    fi
    
    if [[ $line =~ ^"search "  ]] ; then
      regex=$(echo $line | sed 's/search//g')
      while read -r chapter ; do
        prefix=$(head -n1 $chapter | sed 's/$/:/g')
        appears=$(grep -E -w -i $regex $chapter | wc -l)
        if [[ $appears -gt 0 ]]; then
          echo "$prefix $appears" >> shows.txt
        fi
      done < $file
      
      if [[ -f shows.txt ]] ; then
        sort shows.txt
        rm shows.txt
      fi
    fi
    
    echo "Enter: number / files / names / stats <chapter-name> / search <word>/ quit"
    
done

