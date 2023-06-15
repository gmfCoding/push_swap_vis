#include "simulation.h"
#include "sort.h"
#include "libft.h"

t_sop get_operation(char *op)
{
	if (ft_strnstr(op, "pa", 10))
		return PA;
	else if (ft_strnstr(op, "pb", 10))
		return PB;
	else if (ft_strnstr(op, "sa", 10))
		return SA;
	else if (ft_strnstr(op, "sb", 10))
		return SB;
	else if (ft_strnstr(op, "ss", 10))
		return SS;
	else if (ft_strnstr(op, "ra", 10))
		return RA;
	else if (ft_strnstr(op, "rb", 10))
		return RB;
	else if (ft_strnstr(op, "rrr", 10))
		return RRR;
	return (ERR);
}

void apply_operation(t_sort *sort, t_sop op)
{
	if (op == PA)
		op_pa(sort);
	else if (op == PB)
		op_pb(sort);
	else if (op == SA)
		op_sa(sort);
	else if (op == SB)
		op_sb(sort);
	else if (op == SS)
		op_ss(sort);
	else if (op == RA)
		op_ra(sort);
	else if (op == RB)
		op_rb(sort);
	else if (op == RRR)
		op_rrr(sort);
}
