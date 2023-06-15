#include "sort.h"

typedef enum e_sop
{
	PA,
	PB,
	SA,
	SB,
	SS,
	RA,
	RB,
	RRR,
	ERR
}			t_sop;

t_sop get_operation(char *op);
void apply_operation(t_sort *sort, t_sop op);
