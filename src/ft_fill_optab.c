/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_optab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:55:44 by tlamart           #+#    #+#             */
/*   Updated: 2019/11/01 00:15:24 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	nb parameters		  		type of parameters (reg dir ind)
**
**		 3 2 1 x				      r d i   r d i   r d i
**	  0b 1 1 1 0       1 1 0  	      1 1 1   1 1 1   1 1 1
**
**									   [1]	   [2]	   [3]
**
**  op.arg & 1 << 11 --> dir_size
**	op.arg & 1 << 10 --> argument's coding byte
*/

static void	ft_add_arg(t_op *optab)
{
	optab[0].arg = 0x2880;
	optab[1].arg = 0x85f4;
	optab[2].arg = 0x853e;
	optab[3].arg = 0x8d24;
	optab[4].arg = 0x8d24;
	optab[5].arg = 0x8dfc;
	optab[6].arg = 0x8dfc;
	optab[7].arg = 0x8dfc;
	optab[8].arg = 0x2080;
	optab[9].arg = 0x4ce0;
	optab[10].arg = 0x4d28;
	optab[11].arg = 0x2080;
	optab[12].arg = 0x85f4;
	optab[13].arg = 0x4ce0;
	optab[14].arg = 0x2080;
	optab[15].arg = 0x2d00;
}

static void	ft_continue(t_op *optab)
{
	ft_strcpy(optab[8].name, "zjmp");
	optab[8].opcode = 0x09;
	ft_strcpy(optab[1].name, "ldi");
	optab[1].opcode = 0x0A;
	ft_strcpy(optab[2].name, "sti");
	optab[2].opcode = 0x0B;
	ft_strcpy(optab[11].name, "fork");
	optab[11].opcode = 0x0C;
	ft_strcpy(optab[13].name, "lld");
	optab[13].opcode = 0x0D;
	ft_strcpy(optab[12].name, "lldi");
	optab[12].opcode = 0x0E;
	ft_strcpy(optab[14].name, "lfork");
	optab[14].opcode = 0x0F;
	ft_strcpy(optab[15].name, "aff");
	optab[15].opcode = 0x10;
	ft_add_arg(optab);
}

void		ft_fill_optab(t_op *optab)
{
	ft_strcpy(optab[0].name, "live");
	optab[0].opcode = 0x01;
	ft_strcpy(optab[9].name, "ld");
	optab[9].opcode = 0x02;
	ft_strcpy(optab[10].name, "st");
	optab[10].opcode = 0x03;
	ft_strcpy(optab[3].name, "add");
	optab[3].opcode = 0x04;
	ft_strcpy(optab[4].name, "sub");
	optab[4].opcode = 0x05;
	ft_strcpy(optab[5].name, "and");
	optab[5].opcode = 0x06;
	ft_strcpy(optab[6].name, "or");
	optab[6].opcode = 0x07;
	ft_strcpy(optab[7].name, "xor");
	optab[7].opcode = 0x08;
	ft_continue(optab);
}
