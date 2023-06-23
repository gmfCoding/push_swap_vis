#include "sort.h"

typedef enum e_sop
{
	ERR = 0,
	PA,
	PB,
	SA,
	SB,
	SS,
	RA,
	RRA,
	RB,
	RRB,
	RRR
}			t_sop;

t_sop get_operation(char *op);
void apply_operation(t_sort *sort, t_sop op);
