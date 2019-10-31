/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 09:03:38 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/25 13:35:23 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"
#include <unistd.h>

/*
**	Same as name above ...
*/

static int	ft_comment(int *x, int *y, char **tab, char *comment)
{
	int			i;
	static int	mul = 0;

	mul++;
	if (mul > 1)
		return (ERR_COM_MUL);
	*x += ft_strlen(COMMENT_CMD_STRING);
	while (ft_isspace(tab[*y][*x]))
		*x += 1;
	if (tab[*y][*x] != '"')
		return (ERR_COM_FORMAT);
	*x += 1;
	i = 0;
	while (tab[*y][*x] && tab[*y][*x] != '"' && i <= COMMENT_LENGTH)
	{
		comment[i] = tab[*y][*x];
		i++;
		*x += 1;
	}
	if (i > COMMENT_LENGTH)
		return (ERR_COM_LEN);
	if (tab[*y][*x] != '"')
		return (ERR_COM_FORMAT);
	comment[i] = '\0';
	return (0);
}

/*
**	Copy the name in header->prog_name, verifying its size,
**	If there are more than one name, an error is diplayed ...
*/

static int	ft_name(int *x, int *y, char **tab, char *name)
{
	int			i;
	static int	mul = 0;

	mul++;
	if (mul > 1)
		return (ERR_NAME_MUL);
	*x += ft_strlen(NAME_CMD_STRING);
	while (ft_isspace(tab[*y][*x]))
		*x += 1;
	if (tab[*y][*x] != '"')
		return (ERR_NAME_FORMAT);
	*x += 1;
	i = 0;
	while (tab[*y][*x] && tab[*y][*x] != '"' && i <= PROG_NAME_LENGTH)
	{
		name[i] = tab[*y][*x];
		i++;
		*x += 1;
	}
	if (i > PROG_NAME_LENGTH)
		return (ERR_NAME_LEN);
	if (tab[*y][*x] != '"')
		return (ERR_NAME_FORMAT);
	name[i] = '\0';
	return (0);
}

/*
**	Determine if it's the name command, the comment one or something else
*/

static int	ft_fill_header(int *x, int *y, char **tab, t_header *header)
{
	if (ft_strnequ(tab[*y] + *x, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (ft_name(x, y, tab, header->prog_name));
	else if (ft_strnequ(tab[*y] + *x, COMMENT_CMD_STRING,
	ft_strlen(COMMENT_CMD_STRING)))
		return (ft_comment(x, y, tab, header->comment));
	return (ERR_INVALID_CMD);
}

/*
**	The function goes through tab to find the NAME & COMMENT_COMMAND
*/

int			ft_header(t_header *header, int *x, int *y, char **tab)
{
	int		status;
	int		cmd;

	status = 0;
	cmd = 0;
	header->magic = COREWAR_EXEC_MAGIC;
	while (!status && tab[*y] && cmd < 2)
	{
		*x = 0;
		while (ft_isspace(tab[*y][*x]))
			*x += 1;
		if (tab[*y][*x] != COMMENT_CHAR && tab[*y][*x])
		{
			cmd++;
			status = ft_fill_header(x, y, tab, header);
		}
		if (!status)
			*y += 1;
	}
	if (!status && cmd < 2)
		status = ERR_CMD;
	return (status);
}
