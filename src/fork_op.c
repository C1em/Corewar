/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 06:56:57 by coremart          #+#    #+#             */
/*   Updated: 2019/10/11 16:35:08 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	fork_op(t_args *args, t_main *main, t_carriage_lst *cge)
{
	int pc;

	main->cge_start = add_carriage(main->cge_start, cge->carriage);
	pc = (cge->op.pc + (args->args[0] % IDX_MOD) < 0)
	? MEM_SIZE + cge->op.pc + (args->args[0] % IDX_MOD)
	: (cge->op.pc + (args->args[0] % IDX_MOD)) % MEM_SIZE;
	main->cge_start->op = (t_op){pc, 0, 0, 0};
	if (main->flag[BONUS_A])
		disp_op(main, "fork", cge);
	if (main->flag[BONUS_W])
		disp_new_carriage_state(main, main->vm->cycle_tot,
		cge->carriage.player, TRUE);
}

void	lfork_op(t_args *args, t_main *main, t_carriage_lst *cge)
{
	int pc;

	main->cge_start = add_carriage(main->cge_start, cge->carriage);
	pc = (cge->op.pc + args->args[0] < 0)
	? MEM_SIZE + ((cge->op.pc + args->args[0]) % MEM_SIZE)
	: (cge->op.pc + args->args[0]) % MEM_SIZE;
	main->cge_start->op = (t_op){pc, 0, 0, 0};
	if (main->flag[BONUS_A])
		disp_op(main, "lfork", cge);
	if (main->flag[BONUS_W])
		disp_new_carriage_state(main, main->vm->cycle_tot,
		cge->carriage.player, TRUE);
}
