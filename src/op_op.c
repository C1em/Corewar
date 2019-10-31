/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 07:07:27 by coremart          #+#    #+#             */
/*   Updated: 2019/10/09 07:07:46 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_op(t_args *args, __attribute__((unused)) t_main *main,
		t_carriage_lst *cge)
{
	cge->carriage.reg[args->args[2] - 1] = cge->carriage.reg[args->args[0] - 1]
	+ cge->carriage.reg[args->args[1] - 1];
	cge->carriage.carry = (cge->carriage.reg[args->args[2] - 1] == 0);
	if (main->flag[BONUS_A])
		disp_op(main, "add", cge);
}

void	sub_op(t_args *args, __attribute__((unused)) t_main *main,
		t_carriage_lst *cge)
{
	cge->carriage.reg[args->args[2] - 1] = cge->carriage.reg[args->args[0] - 1]
	- cge->carriage.reg[args->args[1] - 1];
	cge->carriage.carry = (cge->carriage.reg[args->args[2] - 1] == 0);
	if (main->flag[BONUS_A])
		disp_op(main, "sub", cge);
}
