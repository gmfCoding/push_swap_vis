#include "simulation.h"
#include "sort.h"
#include "libft.h"
#include "ft_printf.h"



t_sop get_operation(char *op)
{
	t_sop ret = ERR;

	if (ft_strncmp(op, "pa", 2) == 0)
		ret = PA;
	else if (ft_strncmp(op, "pb", 2) == 0)
		ret = PB;
	else if (ft_strncmp(op, "sa", 2) == 0)
		ret = SA;
	else if (ft_strncmp(op, "sb", 2) == 0)
		ret = SB;
	else if (ft_strncmp(op, "ss", 2) == 0)
		ret = SS;
	else if (ft_strncmp(op, "rra", 3) == 0)
		ret = RRA;
	else if (ft_strncmp(op, "ra", 2) == 0)
		ret = RA;
	else if (ft_strncmp(op, "rrb", 3) == 0)
		ret = RRB;
	else if (ft_strncmp(op, "rb", 2) == 0)
		ret = RB;
	else if (ft_strncmp(op, "rrr", 2) == 0)
		ret = RRR;
	return (ret);
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
	else if (op == RRA)
		op_rra(sort);
	else if (op == RA)
		op_ra(sort);
	else if (op == RRB)
		op_rrb(sort);
	else if (op == RB)
		op_rb(sort);
	else if (op == RRR)
		op_rrr(sort);
}
