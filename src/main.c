#include <mlx.h>
#include "ft_printf.h"
#include "libft.h"
#include "lst_extra.h"
#include "get_next_line.h"
#include "sort.h"
#include "texture.h"
#include "program.h"
#include "input.h"

#include <unistd.h>
#include <stdlib.h>

int tex_draw_stack(t_program *program, t_texture tex, t_stack *stack, int max)
{
	t_node *node;
	int		y;
	int		y2;
	int		x;

	node = stack->head;
	y = 0;
	while (node)
	{
		x = 0;
		y2 = 0;
		if (y >= tex.height)
			return (0);
		while (y2 < program->line_height)
		{
			while (x < tex.width * ((float)node->value / (float)max))
			{
				pxput(tex, x, y2, 0xFFFFFFFF);
				x++;
			}
			y2++;
			y++;	
		}
	}
	return (0);
}

int	update(t_program *program)
{
	t_texture tex_a;
	t_texture tex_b;

	tex_a = create_texture(program->mlx, program->width / 2, program->sort->a->count);
	tex_b = create_texture(program->mlx, program->width / 2, program->sort->b->count);
	tex_draw_stack(program, tex_a, program->sort->a, 100);
	tex_draw_stack(program, tex_b, program->sort->b, 100);
	push_tex(program, tex_a, vnew(0,0));
	push_tex(program, tex_b, vnew(program->width / 2, 0));
	return (0);
}

int	main(int argc, char **argv)
{
	t_program prog;
	prog.width = 1000;
	prog.height = 1000;
	prog.name = "PUSH SWAP VISUALISER";
	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, prog.width, prog.height, prog.name);
	prog.sort = parse_input(argc, argv);
	
	while(1)
	{
		char *next;
		next = get_next_line(0);
		if (next == NULL)
			continue;
		ft_printf("%s", next);
		free(next);
	}
	mlx_loop_hook(prog.mlx, update, &prog);
	return (0);
}
