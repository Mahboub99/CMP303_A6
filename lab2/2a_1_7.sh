#!/bin/bash

function bin_to_dic {
      ans=0
      bin=$1
      size=`expr length $bin`
      cnt=0
      
      while [ $cnt -lt $size ]
      do
        temp=${bin:cnt:1} 
        pow=$(($size - $cnt - 1)) 
        lvl=$(( 2**$pow))
        acc=$(( $temp * $lvl))
        ans=$(($ans + $acc))
        cnt=$(($cnt + 1))
      done

      echo $ans
}

function dic_to_bin {
     ans=""
     dic=$1
     arr=()
     while [ $dic -gt 0 ]
     do
       if [ $((dic%2)) -eq 0 ]
       then
         arr+=(0)
       else
         arr+=(1) 
       fi
       dic=$((dic/2))
     done
     cnt="${#arr[@]}"
     cnt=$((cnt-1))
     while [ $cnt -ge 0 ]
     do  
       ans+="${arr[cnt]}"
       cnt=$((cnt-1))
     done
    echo $ans
}

function convert {
   
    if [ $# -eq 1 ]
    then
      bin_to_dic $1

    elif [ $# -eq 2 ]
    then
      if [ $1 -eq 1 ]
      then
        bin_to_dic $2
      elif [ $1 -eq 2 ]
      then
        dic_to_bin $2
      else 
        echo "invalid first parameter"
      fi
    else 
      echo "invalid number of parameters"
    fi

}
convert 1 10010
convert 2 5
convert 1100



