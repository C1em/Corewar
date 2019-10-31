/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 07:08:07 by coremart          #+#    #+#             */
/*   Updated: 2019/10/09 07:11:14 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ld_op(t_args *args, t_main *main, t_carriage_lst *cge)
{
	if (args->type[0] & T_DIR)
		cge->carriage.reg[args->args[1] - 1] = args->args[0];
	else
		cge->carriage.reg[args->args[1] - 1] =
		read_bytes(main->vm->arena, cge->op.pc + (args->args[0] % IDX_MOD), 4);
	cge->carriage.carry = (cge->carriage.reg[args->args[1] - 1] == 0);
	if (main->flag[BONUS_A])
		disp_op(main, "ld", cge);
}

void	st_op(t_args *args, t_main *main, t_carriage_lst *cge)
{
	if (args->type[1] & T_IND)
		write_bytes(main->vm->arena, cge->op.pc + (args->args[1] % IDX_MOD),
		cge->carriage.reg[args->args[0] - 1]);
	else
		cge->carriage.reg[args->args[1] - 1] = cge->carriage.reg[args->args[0]
		- 1];
	if (main->flag[BONUS_A])
		disp_op(main, "st", cge);
}

void	lld_op(t_args *args, t_main *main, t_carriage_lst *cge)
{
	if (args->type[0] & T_DIR)
		cge->carriage.reg[args->args[1] - 1] = args->args[0];
	else
		cge->carriage.reg[args->args[1] - 1] = read_bytes(main->vm->arena,
		cge->op.pc + args->args[0], 4);
	cge->carriage.carry = (cge->carriage.reg[args->args[1] - 1] == 0);
	if (main->flag[BONUS_A])
		disp_op(main, "lld", cge);
}
