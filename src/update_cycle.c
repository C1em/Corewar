/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <cbenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:50:50 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/18 11:33:36 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

static t_carriage_lst	*free_carriage(t_carriage_lst *cge)
{
	t_carriage_lst *tmp;

	tmp = cge->next;
	free(cge);
	return (tmp);
}

static t_carriage_lst	*clean_carriage(t_main *main, t_carriage_lst *carriage,
						int max_last_live)
{
	t_carriage_lst	*start;

	start = carriage;
	while (carriage->next)
	{
		if (carriage->next->carriage.last_live <= max_last_live)
		{
			if (main->flag[BONUS_W])
				disp_new_carriage_state(main, main->vm->cycle_tot,
				carriage->next->carriage.player, FALSE);
			carriage->next = free_carriage(carriage->next);
		}
		else
			carriage = carriage->next;
	}
	if (start->carriage.last_live <= max_last_live)
	{
		if (main->flag[BONUS_W])
			disp_new_carriage_state(main, main->vm->cycle_tot,
			start->carriage.player, FALSE);
		return (free_carriage(start));
	}
	return (start);
}

static int				tot_live(int *nbr_live, int nb_player)
{
	int		ret;

	ret = 0;
	while (nb_player--)
		ret += nbr_live[nb_player];
	return (ret);
}

void					update_cycle(t_main *main)
{
	if (++main->vm->cycle_curr >= main->vm->cycle_to_die)
	{
		main->cge_start = clean_carriage(main, main->cge_start,
		main->vm->cycle_tot - main->vm->cycle_to_die);
		if (main->cge_start == NULL)
			declare_winner(main, main->vm->last_player_alive);
		if (tot_live(main->vm->nbr_live, main->nb_player) >= NBR_LIVE
		|| main->vm->check >= MAX_CHECKS)
		{
			main->vm->cycle_to_die -= CYCLE_DELTA;
			main->vm->check = 0;
		}
		main->vm->check++;
		main->vm->cycle_curr = 0;
		if (main->flag[BONUS_L])
			disp_live(main, tot_live(main->vm->nbr_live, main->nb_player));
		ft_bzero(main->vm->nbr_live, sizeof(int) * MAX_PLAYERS);
	}
	if (++main->vm->cycle_tot >= main->dump && main->dump != -1)
		main->flag[BONUS_D] ? d_memory(main) : dump_memory(main);
	if (main->vm->cycle_tot >= main->stop && main->stop != -1)
		disp_cge_and_stop(main);
}
