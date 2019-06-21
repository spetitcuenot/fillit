/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algo_base.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: spetitcu <spetitcu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 13:23:04 by spetitcu     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 13:55:23 by spetitcu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"

int		algo_pos(t_fillit *fillit, int ox, int oy)
{
	int i;

	i = 0;
	while (i < 4)
	{
		fillit->map[fillit->tetris->coord[i].x + ox +
		(fillit->tetris->coord[i].y + oy) * fillit->size] =
		fillit->tetris->letter;
		i++;
	}
	return (1);
}

int		algo_check(t_fillit *fillit, unsigned long ox, unsigned long oy)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (fillit->map[fillit->tetris->coord[i].x + \
			ox + (fillit->tetris->coord[i].y + oy) * fillit->size] != '.')
			return (0);
		i++;
	}
	return (1);
}

int		alog_rec(t_fillit *fillit, unsigned long ox, unsigned long oy)
{
	t_tetriminos	*tmp;

	algo_pos(fillit, ox, oy);
	tmp = fillit->tetris;
	fillit->tetris = fillit->tetris->next;
	if (algo_base(fillit))
		return (1);
	fillit->tetris = tmp;
	clean_tetriminos(fillit);
	return (0);
}

int		algo_base(t_fillit *fillit)
{
	unsigned long	ox;
	unsigned long	oy;
	size_t			i;

	ox = 0;
	oy = 0;
	i = 0;
	if (!fillit->tetris)
		return (1);
	while (i < fillit->size_total)
	{
		if ((ox <= fillit->size - fillit->tetris->xmax) \
			&& (oy <= fillit->size - fillit->tetris->ymax))
			if (algo_check(fillit, ox, oy))
				if (alog_rec(fillit, ox, oy))
					return (1);
		ox++;
		if (!(++i % fillit->size))
		{
			oy++;
			ox = 0;
		}
	}
	return (0);
}
