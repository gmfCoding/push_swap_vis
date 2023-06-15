#ifndef PROGRAM_H
# define PROGRAM_G
#include "sort.h"
#include "texture.h"

typedef struct s_program t_program;

struct s_program
{
	void *mlx;
	void *win;

	int	width;
	int	height;
	char	*name;
	int	line_height;
	t_texture tex_a;
	t_texture tex_b;
	t_sort *sort;
};
#endif
