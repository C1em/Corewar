/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:29:49 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/03 20:57:44 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_labelize(t_list *label, t_list *instr_lst)
{
	while (instr_lst->next)
		instr_lst = instr_lst->next;
	while (label)
	{
		if (LABEL_CNT->instr == NULL)
			LABEL_CNT->instr = (t_instr*)instr_lst->content;
		label = label->next;
	}
}
