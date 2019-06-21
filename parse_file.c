/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: spetitcu <spetitcu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 19:27:52 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/06/20 12:52:09 by spetitcu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"

static int			check_coord(char *buff, int i)
{
	int				links;

	links = 0;
	if (i < 19 && buff[i + 1] == '#')
		links++;
	if (i >= 1 && buff[i - 1] == '#')
		links++;
	if (i >= 5 && buff[i - 5] == '#')
		links++;
	if (i <= 14 && buff[i + 5] == '#')
		links++;
	return (links);
}

static int			check_tetris(char *buff, int len)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (++i < len)
		if (buff[i] == '.')
			count++;
	return (count);
}

static int			check_buff(char *buff)
{
	size_t			i;
	int				nb_hash;
	int				links;
	int				links_sum;
	size_t			len;

	i = -1;
	nb_hash = 0;
	links_sum = 0;
	while (++i < (len = ft_strlen(buff)))
	{
		if ((buff[i] != '\n' && buff[i] != '#' && buff[i] != '.') 	\
				|| (i % 5 == 4 && buff[i] != '\n'))
			return (0);
		if (buff[i] == '#')
		{
			if (!(links = check_coord(buff, i)))
				return (0);
			links_sum += links;
			nb_hash++;
		}
	}
	if (check_tetris(buff, len) != 12)
		return (0);
	return ((nb_hash == 4 && (links_sum > 4 && links_sum < 9)) ? 1 : 0);
}

void				ft_new_elem(char *buff, t_fillit *fillit, int i)
{
	t_tetriminos	*new;
	t_tetriminos	*tmp;

	if (!(new = (t_tetriminos *)malloc(sizeof(*new))))
		ft_error("error");
	new->letter = 'A' + i;
	add_coord(new, buff);
	new->next = NULL;
	if (fillit->tetris)
	{
		tmp = fillit->tetris;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		fillit->tetris = new;
}

int					parse_file(char *f, t_fillit *fillit)
{
	int				fd;
	char			buff[BUFF_SIZE + 1];
	int				read_size;
	int				i;

	i = 0;
	read_size = 0;
	fd = open(f, O_RDONLY);
	if ((read_size = read(fd, buff, 0)) < 0)
		return (0);
	while ((read_size = read(fd, buff, BUFF_SIZE)))
	{
		if (read_size < 20)
			ft_error("error");
		buff[read_size] = '\0';
		fillit->nb++;
		if (fillit->nb > 26 || !check_buff(buff))
			ft_error("error");
		ft_new_elem(buff, fillit, i++);
	}
	fillit->size = ft_sqrt(4 * fillit->nb);
	fillit->size_total = fillit->size * fillit->size;
	close(fd);
	return (ft_strlen(buff) != 20 ? 0 : 1);
}
