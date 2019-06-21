/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fillit.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: spetitcu <spetitcu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 17:56:46 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2019/06/20 11:26:26 by spetitcu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# define BUFF_SIZE 21

typedef struct			s_coord
{
	size_t				x;
	size_t				y;
}						t_coord;

typedef struct			s_tetriminos
{
	char				letter;
	t_coord				coord[4];
	size_t				xmax;
	size_t				ymax;
	struct s_tetriminos *next;
}						t_tetriminos;

typedef struct			s_fillit
{
	size_t				size;
	size_t				size_total;
	int					nb;
	char				*map;
	t_tetriminos		*tetris;
}						t_fillit;

int						parse_file(char *f, t_fillit *fillit);
void					add_coord(t_tetriminos *tetris, char *buff);
int						algo_base(t_fillit *fillit);
void					clean_tetriminos(t_fillit *fillit);

#endif
