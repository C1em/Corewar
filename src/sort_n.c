/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:02:55 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/11 17:39:22 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	check_valid_n(t_main *main, t_champ *champ)
{
	int		i;

	i = -1;
	while (++i < main->nb_player)
		if (champ[i].lst_pos >= main->nb_player)
			disp_error(set_msg(EXIT_FAILURE, "Error: invalid -n", main), main);
}

static int	is_lock(t_main *main, t_champ *champ, int nb_player, int pos)
{
	int		i;
	int		ret;

	i = -1;
	ret = -1;
	while (++i < nb_player)
		if (champ[i].lst_pos == pos)
		{
			if (ret != -1)
				disp_error(set_msg(EXIT_FAILURE,
				"Error: invalid -n", main), main);
			ret = i;
		}
	return (ret);
}

static void	up(t_champ champs[], int start, int stop)
{
	int		i;
	t_champ	tmp1;
	t_champ	tmp2;

	i = start;
	tmp2 = champs[i];
	while (i < stop)
	{
		tmp1 = champs[i + 1];
		champs[i + 1] = tmp2;
		tmp2 = tmp1;
		i++;
	}
	champs[start] = tmp2;
}

static void	down(t_champ champs[], int start, int stop)
{
	int		i;
	t_champ	tmp1;
	t_champ	tmp2;

	i = start;
	tmp2 = champs[i];
	while (i > stop)
	{
		tmp1 = champs[i - 1];
		champs[i - 1] = tmp2;
		tmp2 = tmp1;
		i--;
	}
	champs[start] = tmp2;
}

void		sort_lst(t_main *main)
{
	int		i;
	int		pos;

	check_valid_n(main, main->champs);
	i = -1;
	while (++i < main->nb_player)
	{
		if ((pos = is_lock(main, main->champs, main->nb_player, i))
		!= -1 && pos != i)
		{
			pos <= i ? down(main->champs, i, pos) : up(main->champs, i, pos);
			i = -1;
		}
	}
}
