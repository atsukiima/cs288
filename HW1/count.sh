#!/bin/sh

alphabet=(a b c d e f g h i j k l m n o p q r s t u v w x y z)
for x in ${alphabet[@]};do
	count=`ls /bin | egrep "^$x" | wc -l`
	echo "$x $count"
done
