#ifndef PROGRAM_H
# define PROGRAM_H
#include "sort.h"
#include "texture.h"
#include "wait.h"

typedef struct s_program t_program;

struct s_program
{
	void *mlx;
	void *win;

	int	width;
	int	height;
	char	*name;
	int	line_height;
	int max;
	int min;
	int logfd;

	int paused;
	int step;
	
	int force_update;

	t_wait timer;
	int speed;

	t_texture tex_a;
	t_texture tex_b;
	t_sort *sort;
};
#endif
