/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:45:25 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/13 13:07:48 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int			set_msg(int ret, char *msg, t_main *main)
{
	main->error_msg = msg;
	return (ret);
}

void		disp_error(int ret, t_main *main)
{
	ret == EXIT_SUCCESS ?
	set_colors(main, COLOR_GREEN) : set_colors(main, COLOR_LIGHT_RED);
	if (!main->flag[BONUS_V] && ret != EXIT_SUCCESS
	&& ft_strcmp(main->error_msg, USAGE) != SAME)
		write(1, "Error\n", 6);
	else
		ft_putendl(main->error_msg);
	if (main->flag[BONUS_C])
		write(1, COLOR_RESET, 4);
	free_all(main);
	exit(ret);
}
