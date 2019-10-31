/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 17:49:50 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/22 16:10:03 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_check_val(char *val)
{
	int		i;

	i = 0;
	if (val[i] == '-' || val[i] == '+')
		i++;
	while (ft_isdigit(val[i]))
		i++;
	while (ft_isspace(val[i]))
		i++;
	return (val[i]);
}

void	ft_write_dir(t_instr *instr, int value, int *idx)
{
	short int	cast;

	if (instr->dir_size)
	{
		instr->bytecode[*idx] = (char)(value >> 24);
		instr->bytecode[*idx + 1] = (char)((value << 8) >> 24);
		instr->bytecode[*idx + 2] = (char)((value << 16) >> 24);
		instr->bytecode[*idx + 3] = (char)((value << 24) >> 24);
		*idx += 4;
	}
	else
	{
		cast = (short int)((value << 16) >> 16);
		instr->bytecode[*idx] = (char)(cast >> 8);
		instr->bytecode[*idx + 1] = (char)((cast << 8) >> 8);
		*idx += 2;
	}
}

int		ft_registre(t_instr *instr, char *num)
{
	int		i;

	i = 0;
	while (num[i] && ft_isdigit(num[i]))
		i++;
	while (ft_isspace(num[i]))
		i++;
	if (num[i])
		return (ERR_UNEXPECTED_CHAR);
	instr->bytecode[instr->len] = (char)ft_atoi(num);
	instr->len += 1;
	return (0);
}

int		ft_direct_char(t_instr *instr, char *val)
{
	int		i;
	int		num;

	i = 1;
	if (*val == LABEL_CHAR)
	{
		while (val[i] && ft_strchr(LABEL_CHARS, val[i]))
			i++;
		while (ft_isspace(val[i]))
			i++;
		if (val[i])
			return (ERR_UNEXPECTED_CHAR);
		instr->len += (instr->dir_size ? 4 : 2);
		return (0);
	}
	if (ft_check_val(val))
		return (ERR_UNEXPECTED_CHAR);
	num = ft_atoi(val);
	ft_write_dir(instr, num, &instr->len);
	return (0);
}

int		ft_indirect_char(t_instr *instr, char *val)
{
	int			i;
	short int	num;

	i = 1;
	if (*val == LABEL_CHAR)
	{
		while (val[i] && ft_strchr(LABEL_CHARS, val[i]))
			i++;
		while (ft_isspace(val[i]))
			i++;
		if (val[i])
			return (ERR_UNEXPECTED_CHAR);
		instr->len += 2;
		return (0);
	}
	if (ft_check_val(val))
		return (ERR_UNEXPECTED_CHAR);
	num = (short int)ft_atoi(val);
	instr->bytecode[instr->len] = (char)(num >> 8);
	instr->bytecode[instr->len + 1] = ((num << 8) >> 8);
	instr->len += 2;
	return (0);
}
