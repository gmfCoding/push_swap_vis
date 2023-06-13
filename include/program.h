#include "sort.h"

typedef struct s_program t_program;

struct s_program
{
	void *mlx;
	void *win;

	int	width;
	int	height;
	char	*name;
	int	line_height;
	t_sort *sort;
};
