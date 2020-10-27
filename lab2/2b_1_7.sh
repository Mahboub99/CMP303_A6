#!/bin/bash

function checkPal {
   s=$1
   s=${s,,}
 
   length=`expr length $s`
   half_length=$(($length / 2))
   cnt=0
   is_pal=1
   while [ $cnt -lt $half_length ]
   do 
    mir=$(($size-$cnt-1))
    if [ ${s:cnt:1} != ${s:mir:1} ]
    then 
      is_pal=0
    fi
    cnt=$(($cnt+1))
   done

 echo $is_pal
}

checkPal apple
checkPal Amenicycinema
checkPal LevEL
