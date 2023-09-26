#!/bin/bash

# Conditional statemnts in shel script

read -p "Enter value of a : " a
read -p "Enter value of b : " b

if [ $a -eq $b ]
then 
echo a is equal to b

elif [ $a -lt $b ]
then 
echo a is less than b

else 
echo a is greater than b

fi

# -eq : equal

# -ne : not equal 

# -gt : greater than   

# -ge : greater than equal to  

# -lt : less than 

# -le : less than equal to 


