#!/bin/sh

function reverse(){
	array=($@);
	len=${#array[@]};
	for((i=0,j=len-1;i<j;i++,j--));do
		temp=${array[i]}
		array[$i]=${array[j]}
		array[$j]=$temp
	done;
	echo ${array[@]};
}
function main(){
	in="$1";
	lst=(`ls $in`)
	num=`echo ${lst[@]} | wc -l`
	echo ${lst[@]}
	reverse ${lst[@]}
}
main "$1"


