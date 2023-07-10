#include <time.h>

typedef struct s_wait t_wait;

struct s_wait
{
	double threshold;
	struct timespec begin;
	struct timespec end;
};

void t_wait_create(t_wait *wait, double threshold);
void t_wait_restart(t_wait *wait);
void t_wait_update(t_wait *wait);
double t_wait_elapsed(t_wait *wait);
int	t_wait_check(t_wait *wait);

