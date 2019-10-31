/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:59:59 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/11 17:38:02 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>
#include "libft.h"

void			set_colors(t_main *main, char *color)
{
	if (main->flag[BONUS_C])
		write(1, color, strlen(color));
}

static void		disp_live_header(t_main *main, int tot_live)
{
	set_colors(main, COLOR_YELLOW);
	write(1, "Cycle: ", 7);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr(main->vm->cycle_tot);
	set_colors(main, COLOR_YELLOW);
	write(1, ", period end with a total of ", 29);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr(tot_live);
	set_colors(main, COLOR_YELLOW);
	write(1, " lives\n", 6);
}

void			disp_live(t_main *main, int tot_live)
{
	int		i;

	disp_live_header(main, tot_live);
	i = -1;
	while (++i < main->nb_player)
	{
		write(1, "  player ", 9);
		set_colors(main, COLOR_LIGHT_RED);
		ft_putnbr(i + 1);
		set_colors(main, COLOR_YELLOW);
		write(1, ": ", 2);
		write(1, main->champs[i].name,
		ft_strlen((char *)main->champs[i].name));
		write(1, " ", 1);
		set_colors(main, COLOR_LIGHT_RED);
		ft_putnbr(main->vm->nbr_live[i]);
		set_colors(main, COLOR_YELLOW);
		write(1, " lives\n", 7);
	}
}

void			disp_new_carriage_state(t_main *main, int tot_cycle,
				int player, t_byte state)
{
	set_colors(main, COLOR_YELLOW);
	write(1, "Cycle: ", 7);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr(tot_cycle);
	set_colors(main, COLOR_YELLOW);
	write(1, ", player ", 9);
	set_colors(main, COLOR_LIGHT_RED);
	write(1, main->champs[player].name,
	ft_strlen((char *)main->champs[player].name));
	set_colors(main, COLOR_YELLOW);
	state ? write(1, " create a new carriage\n", 23)
	: write(1, " lost a carriage\n", 17);
}

void			disp_op(t_main *main, char *op, t_carriage_lst *cge)
{
	set_colors(main, COLOR_YELLOW);
	write(1, "Cycle: ", 7);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr(main->vm->cycle_tot);
	set_colors(main, COLOR_YELLOW);
	write(1, ", player ", 9);
	set_colors(main, COLOR_LIGHT_RED);
	write(1, main->champs[cge->carriage.player].name,
	ft_strlen((char *)main->champs[cge->carriage.player].name));
	set_colors(main, COLOR_YELLOW);
	write(1, " do ", 4);
	write(1, op, ft_strlen(op));
	write(1, "\n", 1);
}
