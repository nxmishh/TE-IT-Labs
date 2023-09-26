#!/bin/bash

# Performing arithmatic op

#reading values from user

read -p "Enter value of a : " a
read -p "Enter value of b : " b

#addition of 2 variables a and b

add=$((a + b))
echo addition of a and b is $add

#subtraction of 2 varibales a and b

sub=$((a-b))
echo Subtraction of a and b is $sub

#multiplication of a and b 

mul=$((a*b))
echo Multiplication of a and b is $mul

#Division of a and b

div=$((a/b))
echo division of a and b id $ div
 
#Modulus of a and b is 
mod=$((a%b))
echo modulus of a and b is $mod 
