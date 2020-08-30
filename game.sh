#!/bin/bash

NAME=${NAME-$USER}

make

coords=$(echo "? $NAME"|./users)

if [ "$coords" = "" ] ; then
	read -r -p "please enter your coordinates seperated by a space or a tab:" coords
	echo "+ $NAME $coords" |./users
fi

shoot(){
	wind=$(($RANDOM % 360))
	echo "Wind heading: $wind degrees!"
	read -r -p "throw heading?" heading
	read -r -p "Throw strength?" pow
	read -r -p "throw height (angle)?" angle
	land=$(echo "$coords $pow $heading $angle $windi"|./parabola)
	echo "Balloon landed at $land!"
	for a in $(echo "x $land"|./users); do
		echo "you hit $a."
		wall "$NAME hit $a with a water balloon"
	done
}

map(){
	xy=($coords)
	x=${xy[0]}
	y=${xy[1]}
	for j in $(seq $(($y-10)) $(($y+10))); do
		for i in $(seq $(($x-10)) $(($x+10))); do
			probe=$(echo "x $i $j"|./users)
			if [ "$probe" != "" ] ;then
				if [ "$i" -eq "$x" -a "$j" -eq "$y" ] ;then
					echo -n " @ "
				else
					echo -n " # "
				fi
			else
				echo -n " . "
			fi
		done
		echo
	done
}
