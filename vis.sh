EXEC=./push_swap
VIEWERPATH=./psvisdata
VIEWER=$VIEWERPATH/psvis
LOG=./psvisdata/operations.log
ARGLOG=./psvisdata/args.log
RAND=./psvisdata/rand

# Default values
MIN=-50
MAX=50
SIZE=100
UNIQUE=0
HEADLESS=0
AUTONB=1
CUSTSEED=0
set -x

# Compile rand utility
if [ ! -f $RAND ]; then
	cc $RAND.c -o $RAND
	chmod u+x rand
fi

# Compile visualiser
if [ ! -f $VIEWER ];then
	make -C $VIEWERPATH
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

# Parse command line arguments
while [[ $#>0 ]]; do
	case "$1" in 
				'-s'|'--size')
					SIZE=$2
					shift 2
					continue
			;;	'-M'|'--max')
					MAX=$2
					shift 2
					continue
			;;	'-m'|'--min')
					MIN=$2
					shift 2
					continue
			;;	'-c'|'--copies')
					UNIQUE=1
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
			;; '-v'|'--verbose')
					VERBOSE=1
					shift
					continue;
	esac
	break
done

# If there are remaining arguments we won't use auto number (random numbers)
if [[ $# != 0 ]]; then
	AUTONB=0
fi

# Assume arguments are numbers, otherwise overwrite if AUTONB.
ARGS="$@"
if [[ $AUTONB == 1 ]]; then
##### GENERATE RANDOM NUMBERS #####

## Arguments to use with our custom rand utility.
RANDARGS="--m $MIN --M $MAX --count $SIZE"

if [[ $UNIQUE == 1 ]]; then
	RANDARGS="$RANDARGS --allow-copies"; fi

if [[ $CUSTSEED == 1 ]]; then
	RANDARGS="$RANDARGS --seed $SEED"; fi

# Get the randomly generated values from our rand utility.
ARGS=$($RAND $RANDARGS)
fi

if [[ $HEADLESS == 1 ]]; then
	$EXEC $ARGS
else
	$EXEC $ARGS | $VIEWER $ARGS
fi
