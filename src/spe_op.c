/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spe_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:56:39 by coremart          #+#    #+#             */
/*   Updated: 2019/10/25 14:08:47 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>

void	live_op(t_args *args, t_main *main, t_carriage_lst *cge)
{
	cge->carriage.last_live = main->vm->cycle_tot;
	if (-args->args[0] - 1 < main->nb_player && -args->args[0] > 0)
		main->vm->last_player_alive = -args->args[0] - 1;
	main->vm->nbr_live[cge->carriage.player]++;
	if (main->flag[BONUS_A])
		disp_op(main, "live", cge);
}

void	zjmp_op(t_args *args, __attribute__((unused)) t_main *main,
		t_carriage_lst *cge)
{
	if (cge->carriage.carry)
		cge->op.offset_to_next_op += (args->args[0] % IDX_MOD) - 3;
	if (main->flag[BONUS_A])
		disp_op(main, "zjmp", cge);
}

void	aff_op(t_args *args, __attribute__((unused)) t_main *main,
		t_carriage_lst *cge)
{
	write(1, (char*)&cge->carriage.reg[args->args[0]], 1);
	if (main->flag[BONUS_A])
		disp_op(main, "aff", cge);
}
