/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 15:34:59 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/01 15:41:51 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

static void		fill_arena(t_main *main)
{
	int				i;
	t_carriage_lst	*tmp;

	tmp = main->cge_start;
	i = main->nb_player;
	while (i--)
	{
		ft_memcpy(&main->vm->arena[i * (MEM_SIZE / main->nb_player)],
		main->champs[i].code, main->champs[i].size);
		tmp->op = (t_op){i * (MEM_SIZE / main->nb_player), 0, 0, 0};
		tmp = tmp->next;
	}
}

void			init_vm(t_main *main)
{
	if (!(main->vm = (t_vm*)malloc(sizeof(t_vm))))
		disp_error(set_msg(EXIT_FAILURE, MALLOC_ERR, main), main);
	ft_bzero(main->vm->arena, MEM_SIZE);
	main->vm->cycle_tot = 0;
	main->vm->cycle_curr = 0;
	main->vm->cycle_to_die = CYCLE_TO_DIE;
	ft_bzero(main->vm->nbr_live, sizeof(int) * MAX_PLAYERS);
	main->vm->check = 0;
	main->vm->last_player_alive = main->nb_player - 1;
	fill_arena(main);
}
