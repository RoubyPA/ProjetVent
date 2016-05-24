#! /bin/bash

periode=$(date +%s)

while true
do
   vitesse=$((RANDOM%100))
   let "periode = $periode+1"
   direction=$((RANDOM%4))

   if [ $direction -eq 0 ]
   then
      strDir="N"
   elif [ $direction -eq 1 ]
   then
      strDir="E"
   elif [ $direction -eq 2 ]
   then
      strDir="S"
   elif [ $direction -eq 3 ]
   then
      strDir="W"
   else
      strDir="NNE"
   fi

   ./localSave $vitesse $strDir $periode

   #sleep 1

done
