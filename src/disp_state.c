/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <cbenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:42:59 by coremart          #+#    #+#             */
/*   Updated: 2019/10/18 12:08:18 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

static void		disp_cge_and_stop_body(t_main *main,
						t_carriage_lst *tmp, int *number, int i)
{
	while (tmp)
	{
		if (tmp->carriage.player == i)
			*number += 1;
		tmp = tmp->next;
	}
	set_colors(main, COLOR_YELLOW);
	write(1, "  ", 2);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr(*number);
	set_colors(main, COLOR_YELLOW);
	write(1, " carriage for players ", 22);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr(i + 1);
	write(1, "\n", 1);
}

void			disp_cge_and_stop(t_main *main)
{
	t_carriage_lst	*tmp;
	int				i;
	int				number;

	set_colors(main, COLOR_YELLOW);
	write(1, "Program stop in cycle ", 22);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr(main->vm->cycle_tot);
	set_colors(main, COLOR_YELLOW);
	write(1, " with :\n", 8);
	i = -1;
	while (++i < main->nb_player)
	{
		tmp = main->cge_start;
		number = 0;
		disp_cge_and_stop_body(main, tmp, &number, i);
	}
	if (main->flag[BONUS_C])
		write(1, COLOR_RESET, 4);
	free_all(main);
	exit(EXIT_SUCCESS);
}
