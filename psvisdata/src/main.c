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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_clamp(int value, int min, int max)
{
	if (value > max)
		return (max);
	else if (value < min)
		return (min);
	return (value);
}

char* ftoa(float amount)
{
	int len = snprintf(NULL, 0, "%f", amount);
	char *str2 = malloc(len + 1);
	snprintf(str2, len + 1, "%f", amount);
	return (str2);
}

char* ft_strnjoin(int count, ...)
{
	int i;
   	int len;
	va_list ap;
	char *str;

	i = 0;
	len = 0;
	va_start(ap, count);
	while (i < count)
	{
		len += strlen(va_arg(ap, char *)); 
		i++;
	}
	va_start(ap, count);
	str = calloc(1, len + 1);
	while (count > 0)
	{
		strcat(str, va_arg(ap, char *));
		count--;
	}
	return (str);
}

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

void render_stacks(t_program *program, int update)
{
	static int force_update = 0;
	force_update++;
	if (update || program->force_update || force_update % 75 == 0)
	{
		force_update = 1;
		program->force_update = 0;
		tex_draw_stack(program, program->tex_a, program->sort->a);
		tex_draw_stack(program, program->tex_b, program->sort->b);
	}
	push_tex(program, program->tex_a, vnew(0,0));
	push_tex(program, program->tex_b, vnew(program->width / 2, 0));	
}

double op_per_second(int speed)
{
	const double speeds[] = {0, 0.1, 0.33333, 0.4, 0.5, 0.66666, 1.0, 2.0, 2.5, 5, 10, 15, 20, 25, 30, 50, 100, 150, 200, 300, 500 };
		
	return (speeds[speed]);
}

int apply_push_swap_commands(t_program *program)
{
	int ops = 0;
	int do_op = 1;

	t_wait_update(&program->timer);
	if (t_wait_elapsed(&program->timer) < 1.0 / op_per_second(program->speed))
		return 0;
	if (do_op == 0 || (program->paused && !program->step))
			return 0;
	while (ops < do_op)
	{
		char *op = get_next_line(0);
		if (op == NULL)
			return 0;
		t_sop sop = get_operation(op);
		apply_operation(program->sort, sop);
		free(op);
		if (sop == ERR)
			continue ;
		if (program->paused)
			break ;
		ops++;
	}
	t_wait_restart(&program->timer);	
	program->step = 0;
	return (1);
}

void display_info(t_program *program)
{
	char *str = ft_itoa(program->sort->op_counter);
	mlx_string_put(program->mlx, program->win, 50, 50, 0xFFFFFFFF, str);
	free(str);
	if (op_per_second(program->speed) > 1.0)
	{	
		char *str_ops = ftoa(op_per_second(program->speed));
		char *str_speed = ft_itoa(program->speed);
		str = ft_strnjoin(5, "op / s:  ", str_ops, " (", str_speed, ")");
		free(str_ops);
		free(str_speed);
	}
	else
	{
		char *str_ops = ftoa(1.0 / op_per_second(program->speed));
		char *str_speed = ft_itoa(program->speed);
		str = ft_strnjoin(5, "s / op:  ", str_ops, " (", str_speed, ")");
		free(str_ops);
		free(str_speed);
	}
	mlx_string_put(program->mlx, program->win, 5, program->height - 63, 0xFFFFFFF, str);
	free(str);
	if (program->paused)
		mlx_string_put(program->mlx, program->win, 5, program->height - 50, 0xFFFFFFFF, "Paused");
}

int	update(t_program *program)
{
	mlx_clear_window(program->mlx, program->win);
	render_stacks(program, apply_push_swap_commands(program));
	display_info(program);
	return (0);
}

int on_input(int key, t_program *pg)
{
	if (key == KEY_P)
		pg->paused = !pg->paused;
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_SPACE)
		pg->step = 1;
	int speed = pg->speed;
	if (key == KEY_LSHIFT)
		pg->speed++;
	if (key == KEY_LCTRL)
		pg->speed--;
	if (pg->speed < 0)
		pg->speed = 0;
	if (pg->speed > 20)
		pg->speed = 20;
	if (pg->speed != speed)
		t_wait_create(&pg->timer, 1.0 / op_per_second(pg->speed));
	int plh = pg->line_height;
	if (key == KEY_PERIOD)
		pg->line_height = ft_clamp(pg->line_height + 1, 1, 10);
	if (key == KEY_COMMA)
		pg->line_height = ft_clamp(pg->line_height - 1, 1, 10);
	if (plh != pg->line_height)
		pg->force_update = 1;
	if (key == KEY_ENTER)
		stn_print(pg->sort);
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
	prog.line_height = 9;
	prog.mlx = mlx_init();
	if (argc == 1)
		return (-1);
	prog.logfd = open(argv[1], O_RDONLY);
	prog.win = mlx_new_window(prog.mlx, prog.width, prog.height, prog.name);
	prog.sort = ft_calloc(sizeof(t_sort), 1);
	prog.sort->a = st_new("a");
	prog.sort->b = st_new("b");
	parse(prog.sort, argc, argv);
	prog.speed = 3;
	prog.paused = 1;
	t_wait_create(&prog.timer, 1.0 / op_per_second(prog.speed));
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
