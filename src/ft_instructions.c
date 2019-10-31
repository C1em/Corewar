/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instructions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:39:14 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/25 18:46:27 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_label_or_not(char **tab, t_cursor *cursor,
		t_list **label, t_list **instr)
{
	int				i;
	int				*x;
	static t_op		optab[16] = {{"", 0, 0, 0, 0}};
	char			*line;

	i = 0;
	x = &cursor->x;
	line = tab[cursor->y];
	if (optab[0].name[0] == '\0')
		ft_fill_optab(optab);
	while (line[*x + i] && ft_strchr(LABEL_CHARS, line[*x + i]))
		i++;
	if (line[*x + i] == LABEL_CHAR)
		return (ft_add_label(line, label, instr, cursor));
	i = 0;
	while (i < 16 && !ft_strnequ(line + *x, optab[i].name,
	ft_strlen(optab[i].name)))
		i++;
	if (0 <= i && i < 16)
	{
		*x += ft_strlen(optab[i].name);
		return (ft_add_instr(cursor, label, instr, optab[i]));
	}
	return (ERR_INVALID_INSTR);
}

int		ft_instr(char **line, t_cursor *cursor, t_list **instr, t_header *h)
{
	t_list	*label;
	char	*com;
	int		status;

	label = NULL;
	status = 0;
	while (line[cursor->y] && !status)
	{
		if ((com = ft_strchr(line[cursor->y], COMMENT_CHAR)))
			*com = '\0';
		cursor->x = 0;
		while (ft_isspace(line[cursor->y][cursor->x]))
			cursor->x += 1;
		if (line[cursor->y][cursor->x])
			status = ft_label_or_not(line, cursor, &label, instr);
		if (!status)
			cursor->y += 1;
	}
	if (!status)
		status = ft_fill_gap(*instr, &label, h);
	return (status);
}
