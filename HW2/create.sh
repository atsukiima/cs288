#!/bin/sh

d=$1		#depth
b=$2		#breadth
root=$3		#root directory
option=$4	#depth or breadth
cd $root
function depth(){
	echo "depth!"
}
function breadth(){
	echo "breadth!"
	open=($root)
	for((i=1;i<=$d;i++));do
		for x in ${open[@]};do
			temp=()
			for((k=1;k<=$b;k++));do
				echo "$x/$k"		#change to 'mkdir'
				temp=(${temp[@]} "$x/$k")
			done
			open=(${open[@]:1} ${temp[@]})
			echo ${open[@]}
		done
	done
}

if [ "$option" = "depth" ];then
	depth
elif [ "$option" = "breadth" ];then
	breadth
else
	echo "option \"$option\" not recognized..."
fi

