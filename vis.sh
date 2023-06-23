EXEC=./push_swap
VIEWERPATH=./psvisdata
VIEWER=$VIEWERPATH/psvis
LOG=./psvisdata/operations.log
ARGLOG=./psvisdata/args.log
RAND=./psvisdata/rand

MIN=-50
MAX=50
SIZE=100
UNIQUE=1

AUTONB=0
if [ ! -f $RAND ]; then
	cc $RAND.c -o $RAND
	chmod u+x rand
fi


if [ ! -f $VIEWER ];then
	make -C $VIEWERPATH
fi

if [[ $# == 0 ]]; then
	AUTONB=1
fi

if [[ "$@" =~ '--help' ]]
then
	(echo -e "Push swap visualiser:
	./psvis.sh [-hsmMce] [numbers...]

	--help
		displays this help message.

	-s --size<number>
		executes push_swap with <number> random integers.
	
	-m --min<number>
		minimum inclusive number used in --size.
	
	-M --max<number>
   		maximum inclusive random number used in --size.
	
	-c --copies
   		allows multiple copies of the same number.
	
	-e --exec
		file path to the push_swap executable.
	")
	exit;
fi

while [[ $#>0 ]]; do
	case "$1" in 
			'-s'|'--size')
					AUTONB=1
					SIZE=$2
					shift 2
					continue
			;;
			'-M'|'--max')
					AUTONB=1
					MAX=$2
					shift 2
					continue
			;;	'-m'|'--min')
					AUTONB=1
					MIN=$2
					shift 2
					continue
			;;	'-c'|'--copies')
					AUTONB=1
					UNIQUE=0
					shift
					continue
			;;	'-e'|'--exec')
					EXEC=$2
					shift 2
					continue
	esac
	break
done

if [[ $AUTONB == 0 ]]
then
ARGS="$@"
else

#if [[ $MIN > $MAX ]]
#then
#	echo "Min is greater than max, switching!"
#		TEMPNB=$MIN
#	MIN=$MAX
#	MAX=$TEMPNB
#fi 

#if [[ $SIZE > $(($MAX-$MIN)) ]]
#then
#	echo "Size is greater than the range, extending the range!"
#	SIZE=$(($MAX-$MIN))
#	MIN=$(($SIZE/-2))
#	MAX=$(($SIZE/2))
#fi
#
#while [[ $SIZE > 0 ]]
#do
#	VAL=$(awk -v min=$MIN -v max=$MAX -v seed=$RANDOM 'BEGIN{srand(seed+0); print int(min+rand()*(max-min+1))}') 
#	if [[ $ARGS =~ (^|[[:space:]])$VAL($|[[:space:]]) ]]; then
#			continue;
#	else
#		ARGS="$ARGS $VAL"
#	fi
#	SIZE=$(($SIZE-1))
#done


RANDARGS="--m $MIN --M $MAX --count $SIZE"
if [[ $UNIQUE == 1 ]]; then
	RANDARGS="$RANDARGS --allow-copies"
fi
echo "$ARGS"

ARGS=$($RAND $RANDARGS)

echo "$ARGS"
#$EXEC $ARGS > $LOG
#$VIEWER $LOG $ARGS
fi
echo "$ARGS"
#> $ARGLOG
$EXEC $ARGS | $VIEWER $ARGS
