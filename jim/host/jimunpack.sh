#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)jimunpack.sh	1.1.1.3	(6/5/87)

# jim now only saves modified files in the jim.recover file, so 
# the -m option is essentially equivalent to the -f option
case "$1" in
m)	modified=modified ;;
-m)	;;
*)	echo 1>&2 jimunpack should only be run from jim.recover; exit 1
esac
file=$2
shift; shift
force=false

for i in $*	# must say $* because if no args left, "for i" executes once anway!
do
	case "$i" in
	# table of contents
	-t)	echo "$file (${modified-not modified})"
		# exit 0
		;;
	-tf|-ft) echo "$file (${modified-not modified})"
		 force=true
		 ;;
	# modified files only ... (archaic -- all files were modified if saved)
	-m)	case ${modified-false} in
		false)	exit 0
		esac
		;;
	# force all files to be recovered
	-f)	force=true
		;;
	-*)	echo 1>&2 "usage: jim.* [-t] [-f] [ files... ]"
		exit 1
		;;
	*)	looking=___unlikelyfilename
		case $i in
		$file)	looking=$file
			break
			;;
		esac
	esac
done

case ${looking-$file} in
___unlikelyfilename)	exit 0 ;;
$file)	;;
esac

(case $force in
false)	echo  "$file (${modified-not modified})? \c"
	read x
	case $x in
	[yY]*)	exit 0;;	# the && succeeds
	*)	exit 1;;	# the && fails
	esac
esac ) </dev/tty && (cat  > $file;echo "Recovered $file")
