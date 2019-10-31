/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 09:25:45 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/22 15:27:26 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op_asm.h"
# include "libft.h"

/*
**	main.c
*/

# define EMPTY_ARG "Error: Argument is empty.\n"
# define WRONG_TYPE_OF_FILE "Error: Wrong type of file, expecting .s.\n"
# define OVERRIDE "Error: File already exists.\n"

/*
**	ft_asm.c
*/

typedef struct	s_cursor
{
	int			fd;
	int			x;
	int			y;
	char		**tab;
}				t_cursor;

void			ft_asm(char *file);

/*
**	ft_fill_header.c
*/

# define ERR_INVALID_CMD		1
# define ERR_NAME_MUL			2
# define ERR_NAME_FORMAT		3
# define ERR_NAME_LEN			4
# define ERR_COM_MUL			5
# define ERR_COM_FORMAT			6
# define ERR_COM_LEN			7
# define ERR_EOF				8
# define ERR_CMD				9

int				ft_header(t_header *header, int *x, int *y, char **tab);

/*
** ft_instructions.c
*/

# define ERR_INVALID_INSTR		13

typedef struct	s_op
{
	char		name[6];
	char		opcode;
	char		param;
	char		dir_size;
	short int	arg;
}				t_op;

typedef struct	s_instr
{
	char		bytecode[20];
	int			len;
	int			pc;
	char		*line;
	char		dir_size;
}				t_instr;

typedef struct	s_label
{
	char		*name;
	t_instr		*instr;
}				t_label;

int				ft_instr(char **line, t_cursor *cursor,
				t_list **instr, t_header *h);

/*
** ft_add_instr.c
*/

# define LABEL_CNT ((t_label*)(label->content))
# define ERR_UNEXPECTED_CHAR	10

int				ft_add_instr(t_cursor *cursor,
				t_list **label_lst, t_list **instr_lst,
				t_op op);
int				ft_err_del_lab(t_list **label_lst, int err);
void			ft_labeldel(void *ptr, size_t size);
void			ft_fill_optab(t_op *optab);

/*
** ft_param.c
*/

int				ft_registre(t_instr *instr, char *num);
int				ft_direct_char(t_instr *instr, char *val);
int				ft_indirect_char(t_instr *instr, char *val);
void			ft_write_dir(t_instr *instr, int value, int *idx);

/*
** ft_label.c
*/

void			ft_labelize(t_list *label_lst, t_list *instr_lst);

/*
** ft_add_label.c
*/

int				ft_add_label(char *line, t_list **label_lst, t_list **instr_lst,
				t_cursor *cursor);

/*
** ft_fill_gap.c
*/

# define ERR_LABEL 				11
# define INSTR_CNT ((t_instr*)(instr_lst->content))

int				ft_fill_gap(t_list *instr_lst, t_list **label_lst,
				t_header *header);

/*
** ft_write.c
*/

# define ERR_CHAMP_SIZE			12

int				ft_write(t_header *header, t_list *instr_lst,
				char *file, int status);

#endif
