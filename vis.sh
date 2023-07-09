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
HEADLESS=0
AUTONB=0
CUSTSEED=0

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
	./psvis.sh [-hsmMsce] [numbers...]

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
	
	-d --seed
		seed to use to generate random numbres.

	-e --exec
		file path to the push_swap executable.
	
	-h --headless
		runs push_swap without the visualiser.
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
			;;	'-M'|'--max')
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
			;;	'-d'|'--seed')
					CUSTSEED=1
					SEED=$2
					shift 2
					continue
			;;	'-e'|'--exec')
					EXEC=$2
					shift 2
					continue
			;;	'-h'|'--headless')
					HEADLESS=1
					shift
					continue
	esac
	break
done

if [[ $AUTONB == 0 ]]
then
ARGS="$@"
else

RANDARGS="--m $MIN --M $MAX --count $SIZE"
if [[ $UNIQUE == 1 ]]; then
	RANDARGS="$RANDARGS --allow-copies"
fi

if [[ $CUSTSEED == 1 ]]; then
	RANDARGS="$RANDARGS --seed $SEED"
fi

echo "$ARGS"
ARGS=$($RAND $RANDARGS)

echo "$ARGS"
#$EXEC $ARGS > $LOG
#$VIEWER $LOG $ARGS
fi
echo "$ARGS"
#> $ARGLOG
if [[ $HEADLESS == 1 ]]; then
	$EXEC $ARGS
else
	$EXEC $ARGS | $VIEWER $ARGS
fi
