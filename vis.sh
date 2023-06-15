EXEC=./push_swap

MIN=-50
MAX=50
SIZE=100
UNIQUE=1

FOUND=0

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
else
	if [[ "$@" =~ '--size' ]]
	then
		MIN=$1
	fi
fi

while [[ $#>0 ]]; do
	case "$1" in 
			'-s'|'--size')
					FOUND=1
					SIZE=$2
					shift 2
					continue
			;;
			'-M'|'--max')
					FOUND=1
					MAX=$2
					shift 2
					continue
			;;	'-m'|'--min')
					FOUND=1
					MIN=$2
					shift 2
					continue
			;;	'-c'|'--copies')
					FOUND=1
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

echo "$@"
if [[ $FOUND == 0 ]]
then
$EXEC $@ | ./psvis $@
else

if [[ $MIN > $MAX ]]
then
	echo "Min is greater than max, switching!"
		TEMPNB=$MIN
	MIN=$MAX
	MAX=$TEMPNB
fi

if [[ $SIZE > $(($MAX-$MIN)) ]]
then
	echo "Size is greater than the range, extending the range!"
	SIZE=$(($MAX-$MIN))
	MIN=$(($SIZE/-2))
	MAX=$(($SIZE/2))
fi

while [[ $SIZE > 0 ]]
do
	VAL=$(awk -v min=$MIN -v max=$MAX -v seed=$RANDOM 'BEGIN{srand(seed+0); print int(min+rand()*(max-min+1))}') 
	if ! [[ ARGS =~ VAL ]];then
		ARGS="$ARGS $VAL"
	fi
	SIZE=$(($SIZE-1))
done
$EXEC $ARGS | ./psvis $ARGS
fi
