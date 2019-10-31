/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:12:19 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/07 21:02:54 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

static void					get_champ_code(int fd, unsigned int exec_code_size,
							t_main *main, const int index)
{
	t_byte	buff[CHAMP_MAX_SIZE];

	if (exec_code_size > CHAMP_MAX_SIZE)
		disp_error(set_msg(EXIT_FAILURE, "Error : champ too big", main), main);
	main->champs[index].size = exec_code_size;
	if (read(fd, buff, exec_code_size) != exec_code_size)
		disp_error(set_msg(EXIT_FAILURE, READ_ERR, main), main);
	ft_memcpy(main->champs[index].code, buff, exec_code_size);
	if (read(fd, buff, 1))
		disp_error(set_msg(EXIT_FAILURE, READ_ERR, main), main);
}

static t_bool				check_null_car(t_byte *const buff, int size)
{
	int		i;

	i = ft_strlen((const char *)buff);
	while (i < size)
		if (buff[i++] != 0)
			return (FAILURE);
	return (SUCCESS);
}

static t_bool				check_header(t_byte *const buff)
{
	int		pos;

	if ((unsigned)read_bytes(buff, 0, MAGIC_HEADER_LEN) != COREWAR_EXEC_MAGIC)
		return (FAILURE);
	pos = MAGIC_HEADER_LEN;
	if (check_null_car(buff + pos, PROG_NAME_LENGTH) != SUCCESS)
		return (FAILURE);
	pos += PROG_NAME_LENGTH;
	if (*((uint32_t*)&buff[pos]) != 0)
		return (FAILURE);
	pos += 8;
	if (check_null_car(buff + pos, COMMENT_LENGTH) != SUCCESS)
		return (FAILURE);
	pos += COMMENT_LENGTH;
	if (*((uint32_t*)&buff[pos]) != 0)
		return (FAILURE);
	return (SUCCESS);
}

void						get_champ(char *file, t_main *main,
							const int index)
{
	int		fd;
	t_byte	buff[HEADER_LENGTH];

	if (++main->nb_player > MAX_PLAYERS)
		disp_error(set_msg(EXIT_FAILURE, "Too many champions", main), main);
	if ((fd = open(file, O_RDONLY)) <= 0)
		disp_error(set_msg(EXIT_FAILURE, OPEN_ERR, main), main);
	if (read(fd, buff, HEADER_LENGTH) != HEADER_LENGTH)
		disp_error(set_msg(EXIT_FAILURE, READ_ERR, main), main);
	if (check_header(buff) == FAILURE)
		disp_error(set_msg(EXIT_FAILURE,
		"ERROR : header not well formated", main), main);
	main->champs[index].lst_pos = -1;
	ft_memcpy(main->champs[index].name, &buff[MAGIC_HEADER_LEN],
	PROG_NAME_LENGTH);
	ft_memcpy(main->champs[index].comment,
	&buff[MAGIC_HEADER_LEN + PROG_NAME_LENGTH + NULL_LEN + EXEC_CODE_LEN],
	COMMENT_LENGTH);
	get_champ_code(fd, (unsigned)read_bytes(buff, MAGIC_HEADER_LEN
	+ PROG_NAME_LENGTH + NULL_LEN, EXEC_CODE_LEN), main, index);
	close(fd);
}
