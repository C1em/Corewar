/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:08:46 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/24 19:41:49 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int		ft_override(char *name, int *fd)
{
	char	ans;
	int		ret;

	perror("");
	ft_putstr("Override ");
	ft_putstr(name);
	ft_putendl(" ? y/n ");
	ret = read(0, &ans, 1);
	if (ret == -1)
		return (-1);
	if (ans == 'n' || ans == 'N')
		return (1024);
	*fd = open(name, O_WRONLY | O_TRUNC);
	return (0);
}

int		ft_get_fd(int *fd, char *file, char **name)
{
	int		i;

	i = ft_strlen(file) - 2;
	file[i] = '\0';
	if (!(*name = ft_strjoin(file, ".cor")))
		return (-1);
	*fd = open(*name, O_EXCL | O_CREAT | O_WRONLY, 0744);
	if (*fd == -1)
		return (ft_override(*name, fd));
	return (0);
}

void	ft_printheader(t_header *header, int fd)
{
	char	magic[4];
	int		prog_size;
	char	size[4];

	magic[0] = (char)(header->magic >> 24);
	magic[1] = (char)((header->magic << 8) >> 24);
	magic[2] = (char)((header->magic << 16) >> 24);
	magic[3] = (char)((header->magic << 24) >> 24);
	write(fd, magic, 4);
	write(fd, header->prog_name, PROG_NAME_LENGTH);
	write(fd, "\0\0\0\0", 4);
	prog_size = header->prog_size;
	size[0] = (char)(prog_size >> 24);
	size[1] = (char)((prog_size << 8) >> 24);
	size[2] = (char)((prog_size << 16) >> 24);
	size[3] = (char)((prog_size << 24) >> 24);
	write(fd, size, 4);
	write(fd, header->comment, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
}

int		ft_write(t_header *header, t_list *instr_lst, char *file, int status)
{
	int		fd;
	char	*name;
	t_list	*to_del;

	to_del = instr_lst;
	name = NULL;
	if (!status)
	{
		if (!(status = ft_get_fd(&fd, file, &name)))
		{
			ft_putstr("Writing output program to ");
			ft_putendl(name);
			ft_printheader(header, fd);
			while (instr_lst)
			{
				write(fd, INSTR_CNT->bytecode, INSTR_CNT->len);
				instr_lst = instr_lst->next;
			}
			close(fd);
		}
	}
	ft_strdel(&name);
	if (instr_lst)
		ft_lstdel(&to_del, &ft_lstdel_cnt);
	return (status);
}
