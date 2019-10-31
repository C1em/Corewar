/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <cbenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 13:51:45 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/25 17:58:49 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include "unistd.h"
#include "stdlib.h"

int				declare_winner(t_main *main, int player_index)
{
	write(1, "Contestant ", 11);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr(player_index + 1);
	set_colors(main, COLOR_GREEN);
	write(1, ", \"", 3);
	set_colors(main, COLOR_LIGHT_RED);
	write(1, main->champs[player_index].name,
	ft_strlen((const char *)main->champs[player_index].name));
	set_colors(main, COLOR_GREEN);
	write(1, "\", has ", 7);
	set_colors(main, COLOR_LIGHT_RED);
	write(1, "won ", 4);
	set_colors(main, COLOR_GREEN);
	write(1, "!\n", 2);
	if (main->flag[BONUS_C])
		write(1, COLOR_RESET, 4);
	free_all(main);
	exit(EXIT_SUCCESS);
}

static void		declare_champ_body(t_main *main, t_champ *champs, int i)
{
	set_colors(main, COLOR_GREEN);
	write(1, "* Player ", 9);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr(i + 1);
	set_colors(main, COLOR_YELLOW);
	set_colors(main, COLOR_GREEN);
	write(1, ", weighing ", 11);
	set_colors(main, COLOR_LIGHT_RED);
	ft_putnbr((int)champs[i].size);
	write(1, " bytes", 6);
	set_colors(main, COLOR_GREEN);
	write(1, ", \"", 3);
	set_colors(main, COLOR_LIGHT_GREEN);
	write(1, champs[i].name,
	strlen((const char *)champs[i].name));
	set_colors(main, COLOR_GREEN);
	write(1, "\" (\"", 4);
	set_colors(main, COLOR_LIGHT_GREEN);
	write(1, champs[i].comment,
	strlen((const char *)champs[i].comment));
	set_colors(main, COLOR_GREEN);
	write(1, "\") !\n", 5);
}

void			declare_champ(t_main *main, t_champ *champs, int nb_player)
{
	int		i;

	set_colors(main, COLOR_YELLOW);
	write(1, "Introducing contestants...\n", 27);
	i = -1;
	while (++i < nb_player)
		declare_champ_body(main, champs, i);
}
