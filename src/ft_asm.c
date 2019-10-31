/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:44:41 by tlamart           #+#    #+#             */
/*   Updated: 2019/11/01 00:04:05 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static void	ft_disp_err(int err, t_cursor *cursor)
{
	static char	errtab[15][42] = {{""}, {"invalid command"}, {"multiple name"},
	{"invalid name format"}, {"Champion name too long (Max length 128)"},
	{"multiple comment"}, {"invalid comment format"}, {"comment is too long"},
	{"reaching eof..."}, {"name or comment is missing"}, {"invalid parameter"},
	{"invalid label"}, {"CHAMP IS TOO BIG !"}, {"invalid instruction/label"}};

	if (err >= 15)
		return ;
	ft_putstr_fd("Error:", 2);
	if (err != ERR_LABEL)
	{
		ft_putnbr_fd(cursor->y + 1, 2);
		ft_putstr_fd(":", 2);
		ft_putnbr_fd(cursor->x, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err > 0)
		ft_putendl_fd(errtab[err], 2);
	else
		perror("");
	if (cursor->tab[cursor->y])
	{
		ft_putchar_fd('\t', 2);
		ft_putendl(cursor->tab[cursor->y]);
	}
}

static int	ft_extendlen(char *str)
{
	int		i;
	int		emptyline;

	i = 0;
	emptyline = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			emptyline++;
		i++;
	}
	return (emptyline + i);
}

static char	*ft_extend(char *buf)
{
	char	*extend;
	int		size;
	int		i;

	size = ft_extendlen(buf);
	if (!ft_isascii(*buf))
		return (NULL);
	if (!(extend = ft_strnew(size)))
		return (NULL);
	i = 0;
	while (*buf)
	{
		extend[i] = *buf;
		i++;
		if (*buf == '\n' && *(buf + 1) == '\n')
		{
			extend[i] = ' ';
			i++;
		}
		buf++;
	}
	extend[i] = '\0';
	return (extend);
}

/*
**	Stock the file in a string, replacing "\n\n" by "\n \n",
**	then split it !
*/

static char	**ft_read_file(int fd, char **tab)
{
	char	*file;
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*tmp;
	char	*extend;

	file = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (!(extend = ft_extend(buf)))
		{
			ft_strdel(&file);
			return (NULL);
		}
		tmp = file;
		file = ft_strjoin(file, extend);
		ft_strdel(&tmp);
		ft_strdel(&extend);
		if (!file)
			return (NULL);
	}
	tab = ft_strsplit(file, '\n');
	ft_strdel(&file);
	return (tab);
}

/*
**	The file is splited into a char** stocked in a struct s_cursor,
**	Then the struct s_header is filled with magic, name and comment,
**	After that, each instruction is translated in bytecode and stock in a list,
**	Finally, everything is written in the .cor file.
*/

void		ft_asm(char *file)
{
	int			status;
	t_header	header;
	t_cursor	cursor;
	t_list		*instr_lst;

	status = 0;
	ft_bzero((void*)&cursor, sizeof(t_cursor));
	if ((cursor.fd = open(file, O_RDONLY)) < 0)
	{
		perror("Error");
		return ;
	}
	if (!(cursor.tab = ft_read_file(cursor.fd, cursor.tab)))
	{
		perror("Error");
		return ;
	}
	close(cursor.fd);
	ft_bzero((void*)&header, sizeof(t_header));
	status = ft_header(&header, &cursor.x, &cursor.y, cursor.tab);
	if (!status)
	{
		instr_lst = NULL;
		status = ft_instr(cursor.tab, &cursor, &instr_lst, &header);
		status = ft_write(&header, instr_lst, file, status);
	}
	if (status)
		ft_disp_err(status, &cursor);
	ft_ctabdel(cursor.tab);
}
