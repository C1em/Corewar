/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:52:16 by coremart          #+#    #+#             */
/*   Updated: 2019/10/10 17:31:12 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	init_main(t_main *main)
{
	ft_bzero(main->champs, sizeof(t_champ) * MAX_PLAYERS);
	main->vm = NULL;
	main->cge_start = NULL;
	main->error_msg = "OK";
	main->nb_player = 0;
	main->dump = -1;
	main->stop = -1;
	ft_bzero(main->flag, sizeof(int) * 7);
}

int			main(int ac, char **av)
{
	t_main	main;

	init_main(&main);
	parse_input(ac - 1, &av[1], &main);
	init_carriage(main.nb_player, &main);
	init_vm(&main);
	declare_champ(&main, main.champs, main.nb_player);
	if (main.flag[BONUS_P])
		disp_error(EXIT_SUCCESS, &main);
	while (1)
	{
		exec_cycle(&main);
		update_cycle(&main);
	}
	free_all(&main);
	return (EXIT_SUCCESS);
}
