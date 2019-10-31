/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:05:46 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/09 16:04:38 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		parse_options(t_main *main, char **av, int *i)
{
	if (ft_strcmp(av[*i] + 1, "dump") == SAME)
		treat_dump(main, av, i);
	else if (ft_strcmp(av[*i] + 1, "s") == SAME)
		treat_stop(main, av, i);
	else if (ft_strcmp(av[*i] + 1, "n") == SAME)
		treat_n(main, av, i);
	else if (*i == 0)
	{
		fill_option(main, av, i);
		*i -= 1;
	}
	else
		disp_error(set_msg(EXIT_FAILURE,
		"Error: wrong argument", main), main);
}

void			parse_input(int ac, char **av, t_main *main)
{
	int		i;

	if (ac == 0)
		disp_error(set_msg(EXIT_FAILURE, USAGE, main), main);
	i = 0;
	while (av[i])
	{
		if (av[i][0] == '-')
			parse_options(main, av, &i);
		else
			get_champ(av[i], main, main->nb_player);
		i++;
	}
	if (main->nb_player < 1)
		disp_error(set_msg(EXIT_FAILURE, "Error: there's no champion", main),
		main);
	sort_lst(main);
}
