/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <cbenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:05:27 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/18 12:07:42 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

void			ft_putnbrhex(t_byte nb)
{
	char	res[2];

	res[0] = "0123456789ABCDEF"[nb >> 4];
	res[1] = "0123456789ABCDEF"[nb & 0x0f];
	write(1, res, 2);
}

void			dump_memory(t_main *main)
{
	int		j;

	j = 0;
	set_colors(main, COLOR_LIGHT_RED);
	while (j < MEM_SIZE)
	{
		write(1, " ", 1);
		ft_putnbrhex(main->vm->arena[j]);
		if (++j % 16 == 0)
			write(1, "\n", 1);
	}
	if (main->flag[BONUS_C])
		write(1, COLOR_RESET, 4);
	free_all(main);
	exit(EXIT_SUCCESS);
}

static void		print_dump_header(t_main *main, int j)
{
	char	*a;
	int		i;

	if (!(a = ft_itoabase(j, "0123456789abcdef")))
		disp_error(set_msg(EXIT_FAILURE, MALLOC_ERR, main), main);
	set_colors(main, COLOR_GREEN);
	write(1, "0x", 2);
	i = ft_strlen(a);
	set_colors(main, COLOR_LIGHT_GREEN);
	while (++i <= 4)
		write(1, "0", 1);
	ft_putstr(a);
	free(a);
	set_colors(main, COLOR_GREEN);
	write(1, " :", 3);
	set_colors(main, COLOR_LIGHT_RED);
}

void			d_memory(t_main *main)
{
	int		j;

	j = 0;
	set_colors(main, COLOR_LIGHT_RED);
	while (j < MEM_SIZE)
	{
		if (j % 64 == 0)
			print_dump_header(main, j);
		write(1, " ", 1);
		ft_putnbrhex(main->vm->arena[j]);
		if (++j % 64 == 0)
			write(1, "\n", 1);
	}
	if (main->flag[BONUS_C])
		write(1, COLOR_RESET, 4);
	free_all(main);
	exit(EXIT_SUCCESS);
}
