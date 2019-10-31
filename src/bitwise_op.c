/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:22:50 by coremart          #+#    #+#             */
/*   Updated: 2019/10/02 01:19:49 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	convert_arg(int arg, t_byte type, t_byte arena[],
			t_carriage_lst *cge)
{
	if (type & T_IND)
		return (read_bytes(arena, cge->op.pc + (arg % IDX_MOD), 4));
	return (cge->carriage.reg[arg - 1]);
}

void		and_op(t_args *args, __attribute__((unused)) t_main *main,
			t_carriage_lst *cge)
{
	cge->carriage.reg[args->args[2] - 1] = ((args->type[0] & T_DIR)
	? args->args[0]
	: convert_arg(args->args[0], args->type[0], main->vm->arena, cge))
	& ((args->type[1] & T_DIR) ? args->args[1]
	: convert_arg(args->args[1], args->type[1], main->vm->arena, cge));
	cge->carriage.carry = (cge->carriage.reg[args->args[2] - 1] == 0);
	if (main->flag[BONUS_A])
		disp_op(main, "and", cge);
}

void		or_op(t_args *args, __attribute__((unused)) t_main *main,
			t_carriage_lst *cge)
{
	cge->carriage.reg[args->args[2] - 1] = ((args->type[0] & T_DIR)
	? args->args[0]
	: convert_arg(args->args[0], args->type[0], main->vm->arena, cge))
	| ((args->type[1] & T_DIR) ? args->args[1]
	: convert_arg(args->args[1], args->type[1], main->vm->arena, cge));
	cge->carriage.carry = (cge->carriage.reg[args->args[2] - 1] == 0);
	if (main->flag[BONUS_A])
		disp_op(main, "or", cge);
}

void		xor_op(t_args *args, __attribute__((unused)) t_main *main,
			t_carriage_lst *cge)
{
	cge->carriage.reg[args->args[2] - 1] = ((args->type[0] & T_DIR)
	? args->args[0]
	: convert_arg(args->args[0], args->type[0], main->vm->arena, cge))
	^ ((args->type[1] & T_DIR) ? args->args[1]
	: convert_arg(args->args[1], args->type[1], main->vm->arena, cge));
	cge->carriage.carry = (cge->carriage.reg[args->args[2] - 1] == 0);
	if (main->flag[BONUS_A])
		disp_op(main, "xor", cge);
}
