#include <mlx.h>
#include <limits.h>

#include "ft_printf.h"
#include "libft.h"
#include "lst_extra.h"
#include "get_next_line.h"
#include "sort.h"
#include "texture.h"
#include "program.h"
#include "input.h"
#include "push_swap/include/program.h"
#include "simulation.h"
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h>

void	stn_print(t_sort *sort)
{
	t_node	*a;
	t_node	*b;

	a = sort->a->head;
	b = sort->b->head;
	ft_printf("---------\n");
	while (a || b)
	{
		if (a)
		{
			ft_printf("%d\t", a->value);
			a = a->next;
		}
		else
			ft_printf("\t");
		if (b)
		{
			ft_printf("%d", b->value);
			b = b->next;
		}
		ft_printf("\n");
	}
	ft_printf("---------\n");
	ft_printf("A\tB\n");
	ft_printf("in %d operations.", sort->op_counter);
}


int ft_range(int value, int inmin, int inmax, int outmin, int outmax)
{
	double slope;

	slope = (outmin - outmax) / (double)(inmin - inmax);
	return (outmin + slope * (value - inmin));
}

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}


int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int get_row_colour(int x, int y, float value)
{
	(void)x;
	(void)value;
	if (y % 2 == 0)
		return (0xFFAA00AA) | ((int)(value * 0x0000FF00));
	return (0xFFFFFFFF);
}

int interpolate(int color1, int color2, float fraction)
{
        unsigned char   r1 = (color1 >> 16) & 0xff;
        unsigned char   r2 = (color2 >> 16) & 0xff;
        unsigned char   g1 = (color1 >> 8) & 0xff;
        unsigned char   g2 = (color2 >> 8) & 0xff;
        unsigned char   b1 = color1 & 0xff;
        unsigned char   b2 = color2 & 0xff;

        return (int) ((r2 - r1) * fraction + r1) << 16 |
                (int) ((g2 - g1) * fraction + g1) << 8 |
                (int) ((b2 - b1) * fraction + b1);
}

int tex_draw_stack(t_program *program, t_texture tex, t_stack *stack)
{
	t_node *node;
	int		y;
	int		y2;
	int		x;
	static int column;

	y = 0;
	while (y < tex.height)
	{
		x = 0;
		while (x < tex.width)
		{
			pxput(tex, x, y, 0xFF000000);
			x++;
		}
		y++;
	}
	node = stack->head;
	y = 0;
	column = 0;
	while (node)
	{
		y2 = 0;
		while (y2 < program->line_height)
		{
			if (y >= tex.height)
				return (0);
			x = 0;
			while (x < tex.width)
			{
				if (x < ft_range(node->value, program->min, program->max, 0, tex.width - 1) + 1)
					pxput(tex, x, y, interpolate(0xFFFF0000, 0xFF00FF00, node->value / (float)program->max));
				else
					break;
				x++;
			}
			y2++;
			y++;
		}
		column++;
		node = node->next;
	}
	return (0);
}

int stack_get_min(t_stack *stack)
{
	t_node *node;
	int max;

	max = INT_MAX;
	node = stack->head;
	while (node)
	{
		if (node->value < max)
			max = node->value;
		node = node->next;
	}
	return (max);
}

int stack_get_max(t_stack *stack)
{
	t_node *node;
	int min;

	min = INT_MIN;
	node = stack->head;
	while (node)
	{
		if (node->value > min)
			min = node->value;
		node = node->next;
	}
	return (min);
}

void render_stacks(t_program *program)
{
	mlx_clear_window(program->mlx, program->win);
	tex_draw_stack(program, program->tex_a, program->sort->a);
	tex_draw_stack(program, program->tex_b, program->sort->b);
	push_tex(program, program->tex_a, vnew(0,0));
	push_tex(program, program->tex_b, vnew(program->width / 2, 0));	
}


int	update(t_program *program)
{
	// Return from the function if we are paused 
	// and we have not asked for a single operation step
	//ft_printf("%d", program->step);
	if (program->paused && !program->step)
		   return 0;
	program->step = 0;
	
	char *op = get_next_line(0);
	if (op == NULL)
		return 0;
	t_sop sop = get_operation(op);
	apply_operation(program->sort, sop);
	free(op);
	if (sop == ERR)
		return 0;
//	stn_print(program->sort);	
	render_stacks(program);
	char *str = ft_itoa(program->sort->op_counter);
	mlx_string_put(program->mlx, program->win, 50, 50, 0xFFFFFFFF, str);
	free(str);
	return (0);
}


int on_input(int key, t_program *pg)
{
	if (key == KEY_P)
		pg->paused = !pg->paused;
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_SPACE
		pg->step = 1;
	return 0;
}

int	end_program(void *state)
{
	(void)state;
	exit(0);
}

int	main(int argc, char **argv)
{
	t_program prog;
	prog.width = 1000;
	prog.height = 1000;
	prog.name = "PUSH SWAP VISUALISER";
	prog.line_height = 1;
	prog.mlx = mlx_init();
	if (argc == 1)
		return (-1);
	prog.logfd = open(argv[1], O_RDONLY);
	prog.win = mlx_new_window(prog.mlx, prog.width, prog.height, prog.name);
	prog.sort = ft_calloc(sizeof(t_sort), 1);
	prog.sort->a = st_new("a");
	prog.sort->b = st_new("b");
	parse(prog.sort, argc, argv);
	prog.paused = 1;
	prog.max = ft_max(stack_get_max(prog.sort->a), stack_get_max(prog.sort->b));
	prog.min = ft_min(stack_get_min(prog.sort->a), stack_get_min(prog.sort->b));
	prog.tex_a = create_texture(prog.mlx, prog.width / 2 - 10, prog.sort->a->count * prog.line_height);
	prog.tex_b = create_texture(prog.mlx, prog.width / 2 - 10, prog.sort->a->count * prog.line_height);
	mlx_loop_hook(prog.mlx, update, &prog);
	mlx_key_hook(prog.win, on_input, &prog);
	mlx_hook(prog.win, 17, 0, end_program, &prog);
	prog.step = 1;
	mlx_loop(prog.mlx);
	return (0);
}

const char* __asan_default_options() { return "detect_leaks=0";}
