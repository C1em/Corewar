/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:32:39 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/09 08:02:04 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

struct s_args;
struct s_main;
struct s_carriage_lst;
typedef int	t_bool;

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4 * 1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

typedef char	t_arg_type;

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_ALL				7
# define ARG_SIZE (char[5]){0, 1, OP_ARR[cge->op.cur_op - 1].dir_size , 0, 2}

/*
**	operations definitions
*/
# define LIVE_OP {FALSE, {0, 0, 0}, 10 , 4, &live_op}
# define LD_OP {TRUE, {T_DIR | T_IND, T_REG, 0}, 5 , 4, &ld_op}
# define ST_OP {FALSE, {T_REG, T_REG | T_IND, 0}, 5 , 4, &st_op}
# define ADD_OP {TRUE, {T_REG, T_REG, T_REG}, 10 , 4, &add_op}
# define SUB_OP {TRUE, {T_REG, T_REG, T_REG}, 10 , 4, &sub_op}
# define AND_OP {TRUE, {T_ALL, T_ALL, T_REG}, 6 , 4, &and_op}
# define OR_OP {TRUE, {T_ALL, T_ALL, T_REG}, 6 , 4, &or_op}
# define XOR_OP {TRUE, {T_ALL, T_ALL, T_REG}, 6 , 4, &xor_op}
# define ZJMP_OP {FALSE, {0, 0, 0}, 20 , 2, &zjmp_op}
# define LDI_OP {FALSE, {T_ALL, T_DIR | T_REG, T_REG}, 25 , 2, &ldi_op}
# define STI_OP {FALSE, {T_REG, T_ALL, T_DIR | T_REG}, 25 , 2, &sti_op}
# define FORK_OP {FALSE, {0, 0, 0}, 800 , 2, &fork_op}
# define LLD_OP {FALSE, {T_DIR | T_IND, T_REG, 0}, 10 , 4, &lld_op}
# define LLDI_OP {TRUE, {T_ALL, T_DIR | T_REG, T_REG}, 50 , 2, &lldi_op}
# define LFORK_OP {FALSE, {0, 0, 0}, 1000 , 2, &lfork_op}
# define AFF_OP {FALSE, {T_REG, 0, 0}, 2 , 4, &aff_op}

/*
**	operation's array
*/
# define MEM_OP LD_OP, ST_OP
# define OP_OP ADD_OP, SUB_OP
# define BIT_OP AND_OP, OR_OP, XOR_OP
# define INDEX_OP LDI_OP, STI_OP
# define LONG_OP LLD_OP, LLDI_OP, LFORK_OP
# define PART1 LIVE_OP, MEM_OP, OP_OP, BIT_OP, ZJMP_OP
# define PART2 INDEX_OP, FORK_OP, LONG_OP, AFF_OP
# define OP_ARR (t_op_info[16]){PART1, PART2}

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3
# define MAGIC_HEADER_LEN	4
# define NULL_LEN			4
# define EXEC_CODE_LEN		4
# define EXEC_CODE_INDEX MAGIC_HEADER_LEN + PROG_NAME_LENGTH + NULL_LEN
# define END_LENGTH EXEC_CODE_LEN + COMMENT_LENGTH + NULL_LEN
# define HEADER_LENGTH		 EXEC_CODE_INDEX + END_LENGTH

typedef struct		s_op_info
{
	t_bool			carry;
	unsigned char	code_byte[3];
	int				cycles;
	int				dir_size;
	void			(*op_fct)(struct s_args*, struct s_main*,
					struct s_carriage_lst*);
}					t_op_info;

#endif
