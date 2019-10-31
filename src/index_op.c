/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 07:10:39 by coremart          #+#    #+#             */
/*   Updated: 2019/10/11 17:38:14 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ldi_op(t_args *args, t_main *main, t_carriage_lst *cge)
{
	int arg1;
	int arg2;

	if (args->type[0] & T_IND)
		arg1 = read_bytes(main->vm->arena, cge->op.pc
		+ (args->args[0] % IDX_MOD), 4);
	else
		arg1 = (args->type[0] & T_REG) ? cge->carriage.reg[args->args[0] - 1]
		: args->args[0];
	arg2 = (args->type[1] & T_REG) ? cge->carriage.reg[args->args[1] - 1]
	: args->args[1];
	cge->carriage.reg[args->args[2] - 1] = read_bytes(main->vm->arena,
	cge->op.pc + (arg1 + arg2) % IDX_MOD, 4);
	if (main->flag[BONUS_A])
		disp_op(main, "ldi", cge);
}

void	sti_op(t_args *args, t_main *main, t_carriage_lst *cge)
{
	int arg2;
	int arg3;

	if (args->type[1] & T_IND)
		arg2 = read_bytes(main->vm->arena, cge->op.pc
		+ (args->args[1] % IDX_MOD), 4);
	else
		arg2 = (args->type[1] & T_REG) ? cge->carriage.reg[args->args[1] - 1]
		: args->args[1];
	arg3 = (args->type[2] & T_REG) ? cge->carriage.reg[args->args[2] - 1]
	: args->args[2];
	write_bytes(main->vm->arena, cge->op.pc + ((arg2 + arg3) % IDX_MOD),
	cge->carriage.reg[args->args[0] - 1]);
	if (main->flag[BONUS_A])
		disp_op(main, "sti", cge);
}

void	lldi_op(t_args *args, t_main *main, t_carriage_lst *cge)
{
	int arg1;
	int arg2;

	if (args->type[0] & T_IND)
		arg1 = read_bytes(main->vm->arena, cge->op.pc + args->args[0]
		% IDX_MOD, 4);
	else
		arg1 = (args->type[0] & T_REG) ? cge->carriage.reg[args->args[0] - 1]
		: args->args[0];
	arg2 = (args->type[1] & T_REG) ? cge->carriage.reg[args->args[1] - 1]
	: args->args[1];
	cge->carriage.reg[args->args[2] - 1] = read_bytes(main->vm->arena,
	cge->op.pc + arg1 + arg2, 4);
	cge->carriage.carry = (cge->carriage.reg[args->args[2] - 1] == 0);
	if (main->flag[BONUS_A])
		disp_op(main, "lldi", cge);
}
