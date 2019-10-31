/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:33:01 by coremart          #+#    #+#             */
/*   Updated: 2019/10/11 16:34:39 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

t_carriage_lst	*add_carriage(t_carriage_lst *start, t_carriage carriage)
{
	t_carriage_lst *new;

	if (!(new = (t_carriage_lst*)malloc(sizeof(t_carriage_lst))))
		return (NULL);
	new->carriage = carriage;
	new->next = start;
	return (new);
}

void			init_carriage(int nb_player, t_main *main)
{
	int i;

	if (!(main->cge_start = (t_carriage_lst*)malloc(sizeof(t_carriage_lst))))
		disp_error(set_msg(EXIT_FAILURE, MALLOC_ERR, main), main);
	main->cge_start->carriage = (t_carriage){0, FALSE, -1, {-1, }};
	main->cge_start->next = NULL;
	i = 0;
	while (++i < nb_player)
		if (!(main->cge_start = add_carriage(main->cge_start,
		(t_carriage){i, FALSE, -1, {-i - 1, }})))
			disp_error(set_msg(EXIT_FAILURE, MALLOC_ERR, main), main);
}
