#!/bin/bash
rm -rf lab1 #1
mkdir lab1 #2
cp words.txt numbers.txt lab1 #3
cd lab1
paste words.txt numbers.txt > MergedContent.txt #4
head -3 MergedContent.txt #5
sort MergedContent.txt > SortedMergedContent.txt #6
echo "The sorted file is :" #7
cat SortedMergedContent.txt #8
chmod u-r SortedMergedContent.txt #9
cat MergedContent.txt | sort | uniq #10
tr  < SortedMergedContent.txt  '[a-z]' '[A-Z]' #11
echo 'Permission denied as it is prevented anyone from reading the file MergedSortedContent ' #12
chmod u+r SortedMergedContent.txt #13
tr  < SortedMergedContent.txt  '[a-z]' '[A-Z]' 
grep -n '^w.*[0-9]' MergedContent.txt #14
tr < MergedContent.txt 'i' 'o'|paste > NewMergedContent.txt #15
pr -m -t MergedContent.txt NewMergedContent.txt #16
    
