#!/bin/bash


if [ $2 -lt 1 ]
then
	echo "Wrong numbers"
	exit
fi
if [ $3 -lt 1 ]
then
	echo "Wrong numbers"
	exit
fi
if [ $4 -lt 1 ] || [ $4 -gt $3 ] #checking arguments
then
	echo "Wrong numbers"
	exit
fi

if [ ! -d $1 ]; then
  mkdir $1
fi

declare -a dir_names
declare -a file_names


for (( c=1; c<=$3; c++ ))	#create random names for dirs and files
do
	
	dir_names[c]=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w  $(( ( RANDOM % 8 )  + 1 ))  | head -n 1)
	#echo ${dir_names[c]}
done
for (( c=1; c<=$2; c++ ))
do
	
	file_names[c]=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w  $(( ( RANDOM % 8 )  + 1 ))  | head -n 1)
	#echo ${file_names[c]}
done

i=1
let "p=$3 + 1"
var=$1'/'
flag=1
while [ $i -lt $p ]	#make dirs with round robin
do
	for (( c=1; c<=$4; c++))
	do

	var=$var${dir_names[i]}
	mkdir $var
	var=$var'/'

	#echo $var
	let "i++"

	if [ $i -eq $p ]
	then
		flag=0
		break
	fi

	done

	if [ $flag -eq 0 ] 
	then
		break
	fi
	var=$1'/'
	flag=1

done
i=1
let "p=$3 + 1"
var=$1'/'
var2=
flag=1
flag1=1
f=1
let "k=$2 +1"
while [ $f -lt $k ] #insert files into the dirs
do
	var=$var${file_names[f]}
	echo $(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w  $(( ( RANDOM % 128000 )  + 1 ))  | head -n 1) > $var
	var=$1'/'
	let "f++"
	while [ $i -lt $p ]
	do
		for (( c=1; c<=$4; c++))
		do

		var=$var${dir_names[i]}
		var2=$var'/'
		var2=$var2${file_names[f]}
		echo $(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w  $(( ( RANDOM % 131072 )  + 1024 ))  | head -n 1) > $var2
		var=$var'/'

		#echo $var2
		let "i++"
		let "f++"
		if [ $f -eq $k ]
		then
			flag1=0
			break
		fi

		if [ $i -eq $p ]
		then
			flag=0
			break
		fi

		done

		
		var=$1'/'
		flag=1
		if [ $flag -eq 0 ] 
		then
			break
		fi
		if [ $flag1 -eq 0 ] 
		then
			break
		fi

	done
	if [ $flag1 -eq 0 ] 
		then
			break
		fi	
	flag1=1
	i=1



done

