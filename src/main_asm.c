/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 09:17:06 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/23 14:07:57 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/*
** Print the usage if no arg, or more than two.
*/

static int	ft_display_usage(char *exec)
{
	ft_putstr("Usage: ");
	ft_putstr(exec);
	ft_putendl(" <sourcefile.s>");
	return (0);
}

/*
**	Check if the file ends by .s
**	If it doesn't, display an error and stop.
*/

static int	ft_check_name(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (i == 0)
		return (write(2, EMPTY_ARG, ft_strlen(EMPTY_ARG)));
	else if (!(i > 1 && arg[i - 2] == '.' && arg[i - 1] == 's'))
		return (write(2, WRONG_TYPE_OF_FILE, ft_strlen(WRONG_TYPE_OF_FILE)));
	return (0);
}

/*
**	Display usage if arg count isn't equal to 2,
**	else, traduce the file in bytecode if possible
*/

int			main(int ac, char **av)
{
	if (ac != 2)
		return (ft_display_usage(*av));
	if (!ft_check_name(av[1]))
		ft_asm(av[1]);
	return (0);
}
