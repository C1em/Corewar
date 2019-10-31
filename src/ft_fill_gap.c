/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_gap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:22:15 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/25 17:47:52 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_dirlab(char *line, t_instr *instruction,
			t_list *label_lst, int *idx)
{
	int		value;
	int		i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line[i] = '\0';
	while (label_lst && !ft_strequ(((t_label*)(label_lst->content))->name,
	line))
		label_lst = label_lst->next;
	if (!label_lst || !((t_label*)(label_lst->content))->instr)
		return (ERR_LABEL);
	value = ((t_label*)(label_lst->content))->instr->pc - instruction->pc;
	ft_write_dir(instruction, value, idx);
	return (0);
}

static int	ft_indirlab(char *line, t_instr *instr, t_list *label_lst, int *idx)
{
	short int	value;
	int			i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line[i] = '\0';
	while (label_lst && !ft_strequ(((t_label*)(label_lst->content))->name,
	line))
		label_lst = label_lst->next;
	if (!label_lst || !((t_label*)(label_lst->content))->instr)
		return (ERR_LABEL);
	value = (short int)(((t_label*)(label_lst->content))->instr->pc
			- instr->pc);
	instr->bytecode[*idx] = (char)(value >> 8);
	instr->bytecode[*idx + 1] = (char)((value << 8) >> 8);
	*idx += 2;
	return (0);
}

static int	ft_param(char *line, t_instr *instr, t_list *label_lst, int *idx)
{
	while (ft_isspace(*line))
		line++;
	if (*line == 'r')
	{
		*idx += 1;
		return (0);
	}
	else if (*line == DIRECT_CHAR)
	{
		if (*(line + 1) != LABEL_CHAR)
		{
			*idx += instr->dir_size ? 4 : 2;
			return (0);
		}
		else
			return (ft_dirlab(line + 2, instr, label_lst, idx));
	}
	else if (*line == LABEL_CHAR)
		return (ft_indirlab(line + 1, instr, label_lst, idx));
	else
	{
		*idx += IND_SIZE;
		return (0);
	}
}

int			ft_fill_bytecode(char *line, char *bytecode, t_list *label_lst,
			t_instr *instr)
{
	int		idx;
	char	**param;
	int		i;
	int		status;

	idx = (*bytecode == 0x09 || *bytecode == 0x0C || *bytecode == 0x0F
	|| *bytecode == 0x01) ? 1 : 2;
	while (*line && !ft_isspace(*line))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	if (!(param = ft_strsplit(line, SEPARATOR_CHAR)))
		return (-1);
	i = 0;
	status = 0;
	while (param[i] && !status && i < 3)
	{
		status = ft_param(param[i], instr, label_lst, &idx);
		i++;
	}
	ft_ctabdel(param);
	return (status);
}

int			ft_fill_gap(t_list *instr_lst, t_list **label_lst, t_header *header)
{
	int		status;

	status = 0;
	while (instr_lst && !status)
	{
		if (ft_strchr(INSTR_CNT->line, LABEL_CHAR))
			status = ft_fill_bytecode(INSTR_CNT->line,
			INSTR_CNT->bytecode, *label_lst, INSTR_CNT);
		if (!instr_lst->next)
			header->prog_size = ((t_instr*)(instr_lst->content))->pc
			+ ((t_instr*)(instr_lst->content))->len;
		instr_lst = instr_lst->next;
	}
	if (*label_lst)
		ft_lstdel(label_lst, &ft_lstdel_cnt);
	return (status);
}
