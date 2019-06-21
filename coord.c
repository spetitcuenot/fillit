/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   coord.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: spetitcu <spetitcu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/10 19:57:39 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 15:07:57 by spetitcu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"

static void			coord_max(t_tetriminos *tetris)
{
	int				i;

	i = 0;
	tetris->xmax = 0;
	tetris->ymax = 0;
	while (i < 4)
	{
		if (tetris->xmax < tetris->coord[i].x)
			tetris->xmax = tetris->coord[i].x;
		if (tetris->ymax < tetris->coord[i].y)
			tetris->ymax = tetris->coord[i].y;
		i++;
	}
	tetris->xmax++;
	tetris->ymax++;
}

static	void		clean_coord(t_tetriminos *tetris)
{
	int				i;
	size_t			x;
	size_t			y;
	t_tetriminos	*tmp;

	tmp = tetris;
	i = 0;
	x = 3;
	while (i < 4)
	{
		if (tmp->coord[i].x < x)
			x = tmp->coord[i].x;
		i++;
	}
	i = 0;
	y = tmp->coord[0].y;
	while (i < 4)
	{
		tmp->coord[i].x -= x;
		tmp->coord[i].y -= y;
		i++;
	}
	coord_max(tetris);
}

static void			init_coord(int i, int j, t_tetriminos *tetris)
{
	if (i >= 5 && i <= 8)
		i -= 1;
	else if (i >= 10 && i <= 13)
		i -= 2;
	else if (i >= 15 && i <= 18)
		i -= 3;
	tetris->coord[j].x = (i % 4);
	tetris->coord[j].y = (i / 4);
}

void				add_coord(t_tetriminos *tetris, char *buff)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (buff[i])
	{
		if (buff[i] == '#')
			init_coord(i, j++, tetris);
		i++;
	}
	clean_coord(tetris);
}
