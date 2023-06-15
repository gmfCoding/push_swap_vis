#include <mlx.h>
#include <limits.h>

#include "ft_printf.h"
#include "libft.h"
#include "lst_extra.h"
#include "get_next_line.h"
#include "sort.h"
#include "texture.h"
#include "program.h"
#include "push_swap/include/program.h"
#include "simulation.h"

#include <unistd.h>
#include <stdlib.h>

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

int tex_draw_stack(t_program *program, t_texture tex, t_stack *stack, int max)
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
				if (x < tex.width * ((float)node->value / (float)max))
					pxput(tex, x, y, interpolate(0xFFFF0000, 0xFF00FF00, node->value / (float)max));
				else
					pxput(tex, x, y, 0xFF000000);
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

int	update(t_program *program)
{
	char *next;
	next = get_next_line(0);
	usleep(80000);	
	if (next)
	{	
		apply_operation(program->sort, get_operation(next));
		free(next);
	}
	tex_draw_stack(program, program->tex_a, program->sort->a, stack_get_max(program->sort->a));
	tex_draw_stack(program, program->tex_b, program->sort->b, stack_get_max(program->sort->b));
	push_tex(program, program->tex_a, vnew(0,0));
	push_tex(program, program->tex_b, vnew(program->width / 2, 0));
	return (0);
}

int	main(int argc, char **argv)
{
	t_program prog;
	prog.width = 1000;
	prog.height = 1000;
	prog.name = "PUSH SWAP VISUALISER";
	prog.line_height = 10;
	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, prog.width, prog.height, prog.name);
	prog.sort = ft_calloc(sizeof(t_sort), 1);
	prog.sort->a = st_new("a");
	prog.sort->b = st_new("b");
	parse(prog.sort, argc, argv);
	prog.tex_a = create_texture(prog.mlx, prog.width / 2 - 10, prog.sort->a->count * prog.line_height);
	prog.tex_b = create_texture(prog.mlx, prog.width / 2 - 10, prog.sort->a->count * prog.line_height);
	mlx_loop_hook(prog.mlx, update, &prog);
	mlx_loop(prog.mlx);
	return (0);
}

const char* __asan_default_options() { return "detect_leaks=0";}
