/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:50:43 by cbenoit           #+#    #+#             */
/*   Updated: 2019/11/01 00:03:20 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static int			no_code_byte_args(t_carriage_lst *cge, t_vm *vm,
					t_args *args)
{
	int offset;

	if (cge->op.cur_op == 1)
	{
		offset = 5;
		args->args[0] = read_bytes(vm->arena, cge->op.pc + 1, 4);
	}
	else
	{
		offset = 3;
		args->args[0] = read_bytes(vm->arena, cge->op.pc + 1, 2);
		args->args[0] = (int)*(short*)&args->args[0];
	}
	args->nb_args = 1;
	return (offset);
}

int					read_args(t_carriage_lst *cge, t_vm *vm, t_args *args)
{
	int		offset;
	int		type_code;

	if (OP_ARR[cge->op.cur_op - 1].code_byte[0] == 0)
		return (no_code_byte_args(cge, vm, args));
	offset = 2;
	ft_bzero(args, sizeof(t_args));
	args->nb_args = -1;
	while (++args->nb_args < 3
	&& OP_ARR[cge->op.cur_op - 1].code_byte[args->nb_args])
	{
		if ((type_code = (read_bytes(vm->arena, cge->op.pc + 1, 1)
		>> (8 - ((args->nb_args + 1) << 1))) & 0x3) == 0)
			continue ;
		if (type_code == IND_CODE)
			args->type[args->nb_args] = T_IND;
		else
			args->type[args->nb_args] = type_code;
		args->args[args->nb_args] = read_bytes(vm->arena, cge->op.pc + offset,
		ARG_SIZE[args->type[args->nb_args]]);
		offset += ARG_SIZE[args->type[args->nb_args]];
		if (ARG_SIZE[args->type[args->nb_args]] == 2)
			args->args[args->nb_args] = *(short*)&args->args[args->nb_args];
	}
	return (offset);
}

static t_bool		is_args_ok(t_args *args, int op)
{
	int		i;

	i = 0;
	while (i < 3 && OP_ARR[op].code_byte[i])
	{
		if (i >= args->nb_args
		|| (OP_ARR[op].code_byte[i] & args->type[i]) == 0)
			return (0);
		if (args->type[i] & T_REG && (args->args[i] < 1
		|| args->args[i] > REG_NUMBER))
			return (0);
		i++;
	}
	return (1);
}

/*
**	read op, put the cycle to wait, then decrement cycle to wait.
**	at each next cycle decrement cycle to wait and when cycle to wait
**	goes from 1 to 0,
**	read the coding byte(only the bits needed by the op,
**	if the coding byte isn't valid, put bytes_to_jump to 2),
**	put bytes_to_jump, read the args. do nothing if the op is invalid
**	and do the op if it is valid.
**	then at the next cycle add bytes_to_jump to pc, read the op etc etc.
*/

static void			carriage_cycle(t_main *main, t_carriage_lst *cge)
{
	t_args	args;

	if (cge->op.cycle_remaining == 0)
	{
		cge->op.pc = (cge->op.pc + cge->op.offset_to_next_op < 0)
		? MEM_SIZE + ((cge->op.pc + cge->op.offset_to_next_op) % MEM_SIZE)
		: (cge->op.pc + cge->op.offset_to_next_op) % MEM_SIZE;
		cge->op.cur_op = read_bytes(main->vm->arena, cge->op.pc, 1);
		if (cge->op.cur_op > 16 || cge->op.cur_op < 1)
		{
			cge->op.cur_op = 0;
			cge->op.cycle_remaining = 1;
		}
		else
			cge->op.cycle_remaining = OP_ARR[cge->op.cur_op - 1].cycles;
	}
	if (--cge->op.cycle_remaining == 0)
	{
		cge->op.offset_to_next_op = 1;
		if (!cge->op.cur_op)
			return ;
		cge->op.offset_to_next_op = read_args(cge, main->vm, &args);
		if (is_args_ok(&args, cge->op.cur_op - 1))
			OP_ARR[cge->op.cur_op - 1].op_fct(&args, main, cge);
	}
}

void				exec_cycle(t_main *main)
{
	t_carriage_lst	*carriage;

	carriage = main->cge_start;
	while (carriage)
	{
		carriage_cycle(main, carriage);
		carriage = carriage->next;
	}
}
