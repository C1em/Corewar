/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 20:51:06 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/11 17:39:09 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void	fill_bonus(t_main *main, char **av, int *i, int j)
{
	if (av[*i][j] == 'a')
		main->flag[0] = 1;
	else if (av[*i][j] == 'c')
		main->flag[1] = 1;
	else if (av[*i][j] == 'p')
		main->flag[2] = 1;
	else if (av[*i][j] == 'l')
		main->flag[3] = 1;
	else if (av[*i][j] == 'w')
		main->flag[4] = 1;
	else if (av[*i][j] == 'v')
		main->flag[5] = 1;
	else if (av[*i][j] == 'd')
		main->flag[6] = 1;
	else
		disp_error(set_msg(EXIT_FAILURE, "Error: wrong argument", main), main);
}

void		fill_option(t_main *main, char **av, int *i)
{
	int		j;

	while (av[*i] && av[*i][0] == '-')
	{
		if (ft_strcmp(av[*i] + 1, "n") == SAME
		|| ft_strcmp(av[*i] + 1, "s") == SAME
		|| ft_strcmp(av[*i] + 1, "dump") == SAME)
			return ;
		j = 0;
		while (av[*i][++j])
			fill_bonus(main, av, i, j);
		*i += 1;
	}
}

void		treat_n(t_main *main, char **av, int *i)
{
	int		lock_number;

	if (av[*i + 1] && av[*i + 2] && ft_isint(av[*i + 1]))
	{
		lock_number = ft_atoi(av[*i + 1]);
		*i += 2;
		if (lock_number < 1 || lock_number > MAX_PLAYERS)
			disp_error(set_msg(EXIT_FAILURE, "Error : invalid -n", main), main);
		get_champ(av[*i], main, main->nb_player);
		main->champs[main->nb_player - 1].lst_pos = lock_number - 1;
	}
	else
		disp_error(set_msg(EXIT_FAILURE, "Error : invalid -n", main), main);
}

void		treat_dump(t_main *main, char **av, int *i)
{
	if (!av[*i + 1] || !ft_isint(av[*i + 1]))
		disp_error(set_msg(EXIT_FAILURE, "Error : invalid -d", main), main);
	*i += 1;
	main->dump = ft_atoi(av[*i]);
}

void		treat_stop(t_main *main, char **av, int *i)
{
	if (!av[*i + 1] || !ft_isint(av[*i + 1]))
		disp_error(set_msg(EXIT_FAILURE, "Error : invalid -s", main), main);
	*i += 1;
	main->stop = ft_atoi(av[*i]);
}
