#include "wait.h"

void t_wait_create(t_wait *wait, double threshold)
{
	wait->threshold = threshold;
	t_wait_restart(wait);
}

void t_wait_restart(t_wait *wait)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &wait->begin);
	t_wait_update(wait);
}

void t_wait_update(t_wait *wait)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &wait->end);
}

double t_wait_elapsed(t_wait *wait)
{
	const double ns = (wait->end.tv_nsec - wait->begin.tv_nsec);
	const double s = (wait->end.tv_sec - wait->begin.tv_sec);

	return (ns / 1000000000.0 + s);
}

int	t_wait_check(t_wait *wait)
{
	return (wait->threshold <= t_wait_elapsed(wait));
}
