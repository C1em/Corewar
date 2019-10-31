/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:57:01 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/07 21:01:32 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

static void		free_vm(t_vm *vm)
{
	free(vm);
}

static void		free_carriage(t_carriage_lst *carriage_lst)
{
	t_carriage_lst	*next;

	while (carriage_lst)
	{
		next = carriage_lst->next;
		free(carriage_lst);
		carriage_lst = next;
	}
}

void			free_all(t_main *main)
{
	if (main)
	{
		if (main->vm)
			free_vm(main->vm);
		if (main->cge_start)
			free_carriage(main->cge_start);
	}
}
