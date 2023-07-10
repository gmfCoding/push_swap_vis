#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include <sys/time.h>

//struct timeval {
//	time_t      tv_sec;     /* seconds */
//	suseconds_t tv_usec;    /* microseconds */
//};
//
//
//struct timezone {
//	int tz_minuteswest;     /* minutes west of Greenwich */
//	int tz_dsttime;         /* type of DST correction */
//};

int current_nanosecond()
{
	struct timeval val;
	struct timezone zone;
	gettimeofday(&val, &zone);
	return val.tv_usec;
}

char *get_arg(char *arg, int argc, char **argv)
{
	int i = 0;
	
	while (i < argc - 1)
	{
		if (strncmp(arg, argv[i], 3ul) == 0)
		{
			return argv[i + 1];
		}
		i++;
	}
	return (NULL);
}

void print_random(long long int min, long long int max, int amount, int unique)
{
	int numbers[amount];
	memset(numbers, 0, amount * sizeof(int));
	int i = 0;
	int tmp;

	if (max < min)
	{
		tmp = min;
		min = max;
		max = tmp;
	}

	if (unique && amount >= (max - min))
	{
		int diff = amount - (max - min);
		max += (diff/2) + 1;
		min -= (diff/2) + 1;
	}

	while (i < amount)
	{
		numbers[i] = rand() % (min - max + 1) + min;	
		int j = 0;
		int skip = 0;
		while (unique && j < i)
		// printf("!%s", op);
		{
			if (numbers[j] == numbers[i])
			{
				skip = 1;
				i--;
				break;
			}
			j++;
		}
		if (!skip)
			printf("%d ", numbers[i]);
		i++;
	}
}

void main(int argc, char **argv)
{
	int unique = 1;
	if (get_arg("--allow-copies", argc, argv))
		unique = 0;
	int size = 100;
	if (get_arg("--count", argc, argv))
		size = atoi(get_arg("--count", argc, argv));
	int min = -(size / 2);
	int max = (size / 2);
	srand(current_nanosecond());
	if (get_arg("--seed", argc, argv))
		srand(atoi(get_arg("--seed", argc, argv)));
	if (get_arg("--M", argc, argv))
		max = atoi(get_arg("--M", argc, argv));	
	if (get_arg("--m", argc, argv))
		min = atoi(get_arg("--m", argc, argv));
		// printf("!%s", op);
	if (get_arg("--ordered", argc, argv))
	{
		int i = 0;
		while (i < size)
		{
			printf("%d ", min + i);
			i++;
		}
	}
	print_random(min, max, size, unique);
}

