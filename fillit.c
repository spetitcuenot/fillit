/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fillit.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: spetitcu <spetitcu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 14:58:38 by spetitcu     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 14:58:42 by spetitcu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"

void	ft_display(t_fillit *fillit)
{
	size_t		i;

	i = -1;
	while (++i < fillit->size_total)
	{
		ft_putchar(fillit->map[i]);
		if (!((i + 1) % fillit->size))
			ft_putchar('\n');
	}
	ft_strdel(&fillit->map);
}

void	clean_tetriminos(t_fillit *fillit)
{
	int i;

	i = 0;
	while (fillit->map[i])
	{
		if (fillit->map[i] == fillit->tetris->letter)
			fillit->map[i] = '.';
		i++;
	}
}

void	free_tetris(t_tetriminos *tetris)
{
	t_tetriminos	*tmp;

	if (tetris)
		while (tetris)
		{
			tmp = tetris->next;
			free(tetris);
			tetris = NULL;
			tetris = tmp;
		}
}

void	end_fillit(t_fillit *fillit, t_tetriminos *tetris)
{
	free_tetris(tetris);
	ft_display(fillit);
	free(fillit);
}

int		main(int ac, char *av[])
{
	t_fillit		*fillit;
	t_tetriminos	*tmp;

	if (ac != 2)
		ft_error("usage: ./fillit sample_file");
	if (!(fillit = (t_fillit *)malloc(sizeof(*fillit))))
		ft_error("error");
	fillit->tetris = NULL;
	fillit->nb = 0;
	if (!parse_file(av[1], fillit) \
			|| !(fillit->map = ft_strnew(fillit->size_total)))
		ft_error("error");
	ft_memset(fillit->map, '.', fillit->size_total);
	tmp = fillit->tetris;
	while (!algo_base(fillit))
	{
		ft_strdel(&fillit->map);
		fillit->size++;
		fillit->size_total = fillit->size * fillit->size;
		if (!(fillit->map = ft_strnew(fillit->size_total)))
			ft_error("error");
		ft_memset(fillit->map, '.', fillit->size_total);
	}
	end_fillit(fillit, tmp);
	return (0);
}
