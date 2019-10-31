/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_instr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:37:31 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/24 16:59:28 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_err_del_lab(t_list **label_lst, int err)
{
	if (label_lst && *label_lst)
		ft_lstdel(label_lst, &ft_lstdel_cnt);
	return (err);
}

char	ft_param(char *line, t_op o, int i, char byte)
{
	int		pos;

	pos = 6;
	while (line && pos > 0)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i += 1;
		if (line[i] == 'r' && (4 & (o.arg >> (pos - ((6 - pos) / 2)))))
			byte |= (REG_CODE << pos);
		else if (line[i] == DIRECT_CHAR
		&& (2 & (o.arg >> (pos - ((6 - pos) / 2)))))
			byte |= (DIR_CODE << pos);
		else if ((ft_isdigit(line[i]) || line[i] == LABEL_CHAR
		|| line[i] == '-' || line[i] == '+')
		&& (1 & (o.arg >> (pos - ((6 - pos) / 2)))))
			byte |= (IND_CODE << pos);
		else
			return (0);
		if ((line = ft_strchr(line, SEPARATOR_CHAR)))
			line++;
		pos -= 2;
	}
	return (((o.arg << (pos / 2)) & (1 << 15)) ? byte : 0);
}

int		ft_bytecode(t_instr *instr, char *line)
{
	char	**param;
	int		i;
	int		j;
	int		status;

	if (!(param = ft_strsplit(line, SEPARATOR_CHAR)))
		return (-1);
	i = 0;
	status = 0;
	while (param[i] && !status)
	{
		j = 0;
		while (ft_isspace(param[i][j]))
			j++;
		if (param[i][j] == 'r')
			status = ft_registre(instr, param[i] + j + 1);
		else if (param[i][j] == DIRECT_CHAR)
			status = ft_direct_char(instr, param[i] + j + 1);
		else
			status = ft_indirect_char(instr, param[i] + j);
		i++;
	}
	ft_ctabdel(param);
	return (status);
}

int		ft_add_instr(t_cursor *cursor, t_list **label_lst, t_list **instr_lst,
		t_op op)
{
	t_list		*instr_ptr;
	t_instr		instr;
	int			status;
	static int	pc = 0;

	ft_bzero((void*)&instr, sizeof(t_instr));
	instr.line = cursor->tab[cursor->y] + cursor->x;
	instr.bytecode[0] = op.opcode;
	instr.len = 1;
	instr.pc = pc;
	instr.dir_size = op.arg >> 11 & 1;
	if (!(instr.bytecode[instr.len] = ft_param(instr.line, op, 0, 0)))
		return (ft_err_del_lab(label_lst, ERR_UNEXPECTED_CHAR));
	instr.len += (op.arg & (1 << 10)) ? 1 : 0;
	instr.bytecode[instr.len] = 0;
	if ((status = ft_bytecode(&instr, instr.line)))
		return (ft_err_del_lab(label_lst, status));
	pc += instr.len;
	if (!(instr_ptr = ft_lstnew((void*)&instr, sizeof(t_instr))))
		return (ft_err_del_lab(label_lst, -1));
	ft_lstappend(instr_lst, instr_ptr);
	ft_labelize(*label_lst, *instr_lst);
	return (0);
}
