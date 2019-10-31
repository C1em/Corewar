/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 21:41:46 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/24 19:26:56 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_findinstr(char *line, t_list **label_lst, t_list **instr_lst,
			t_cursor *cursor)
{
	int			i;
	static t_op	optab[16] = {{"", 0, 0, 0, 0}};
	int			*x;

	i = 0;
	x = &cursor->x;
	if (optab[0].name[0] == '\0')
		ft_fill_optab(optab);
	while (i < 16 && !ft_strnequ(line + *x, optab[i].name,
	ft_strlen(optab[i].name)))
		i++;
	if (0 <= i && i < 16)
	{
		*x += ft_strlen(optab[i].name);
		return (ft_add_instr(cursor, label_lst, instr_lst, optab[i]));
	}
	else
		return (ft_err_del_lab(label_lst, ERR_UNEXPECTED_CHAR));
}

int			ft_add_label(char *line, t_list **label_lst, t_list **instr_lst,
			t_cursor *cursor)
{
	t_label	label;
	t_list	*label_ptr;
	int		*x;

	x = &cursor->x;
	ft_bzero((void*)&label, sizeof(label));
	label.name = line + *x;
	label.instr = NULL;
	while (ft_strchr(LABEL_CHARS, line[*x]))
		*x += 1;
	if (line[*x] == LABEL_CHAR)
		line[*x] = '\0';
	else
		return (ft_err_del_lab(label_lst, ERR_UNEXPECTED_CHAR));
	if (!(label_ptr = ft_lstnew((void*)&label, sizeof(t_label))))
		return (ft_err_del_lab(label_lst, -1));
	ft_lstappend(label_lst, label_ptr);
	*x += 1;
	if (!line[*x])
		return (0);
	while (ft_isspace(line[*x]))
		*x += 1;
	return (line[*x] ? ft_findinstr(line, label_lst, instr_lst, cursor) : 0);
}
