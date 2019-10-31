/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <cbenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:42:27 by coremart          #+#    #+#             */
/*   Updated: 2019/10/18 12:08:50 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"

/*
**	common define
*/
# define SUCCESS 0
# define FAILURE 1
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define STDIN 0
# define TRUE 1
# define FALSE 0
# define SAME 0

/*
**	common error define
*/
# define OPTION "Usage: corewar [-acplwvd] "
# define OPTION2 "[-dump number | -s number | -n number champ | champ]\n "
# define OPT_A "-a : write each operation done (player name,"
# define OPT_A2 " cycle, carriage number)\n "
# define OPT_C "-c : colorise corewar display\n "
# define OPT_P "-p : stop the program before the first cycle"
# define OPT_P2 " & write parseur state\n "
# define OPT_L "-l : write nb_tot live in the current period for each player\n "
# define OPT_W "-w : write new & lost carriage (name, cycle, msg new/lost)\n "
# define OPT_V "-v : verbose\n -n : give a number to a champion\n "
# define OPT_S "-s : stop le programme au cycle X et "
# define OPT_S2 "indique combien de carriage ont chaques joueurs\n "
# define OPT_D "-d : dump memory like the real corewar\n "
# define OPT_DUMP "-dump : dump memory"
# define PART_2U OPT_W OPT_V OPT_S OPT_S OPT_S2 OPT_D OPT_DUMP
# define USAGE OPTION OPTION2 OPT_A OPT_A2 OPT_C OPT_P OPT_P2 OPT_L PART_2U
# define OPEN_ERR "Error : an error occured on the open"
# define READ_ERR "Error : an error occured in the read"
# define MALLOC_ERR "Error : malloc"

/*
**	color define
*/
# define COLOR_RED "\033[0;31m"
# define COLOR_LIGHT_RED "\033[1;31m"
# define COLOR_GREEN "\033[0;32m"
# define COLOR_LIGHT_GREEN "\033[1;32m"
# define COLOR_YELLOW "\033[0;33m"
# define COLOR_CYAN "\033[0;36m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_RESET "\033[0m"

/*
**	bonus define
*/
# define BONUS_A 0
# define BONUS_C 1
# define BONUS_P 2
# define BONUS_L 3
# define BONUS_W 4
# define BONUS_V 5
# define BONUS_D 6

typedef unsigned char	t_byte;

typedef struct			s_vm
{
	t_byte	arena[MEM_SIZE];
	int		cycle_tot;
	int		cycle_curr;
	int		cycle_to_die;
	int		nbr_live[MAX_PLAYERS];
	int		check;
	int		last_player_alive;
}						t_vm;

typedef struct			s_champ
{
	t_byte			name[PROG_NAME_LENGTH];
	t_byte			comment[COMMENT_LENGTH];
	t_byte			code[CHAMP_MAX_SIZE];
	unsigned int	size;
	int				lst_pos;
}						t_champ;

typedef struct			s_carriage
{
	int					player;
	t_bool				carry;
	int					last_live;
	int					reg[REG_NUMBER];
}						t_carriage;

typedef struct			s_op
{
	int					pc;
	int					cycle_remaining;
	int					offset_to_next_op;
	int					cur_op;
}						t_op;

typedef struct			s_carriage_lst
{
	t_carriage				carriage;
	t_op					op;
	struct s_carriage_lst	*next;
}						t_carriage_lst;

/*
**	cge_start goes from the last player to the newer
*/
typedef struct			s_main
{
	t_champ			champs[MAX_PLAYERS];
	t_vm			*vm;
	t_carriage_lst	*cge_start;
	char			*error_msg;
	int				nb_player;
	int				dump;
	int				stop;
	int				flag[7];
}						t_main;

typedef struct			s_args
{
	int				args[3];
	int				nb_args;
	t_byte			type[3];
}						t_args;

/*
**	parse_input.c
*/
void					parse_input(int ac, char **av, t_main *main);

/*
**	disp_error.c
*/
void					disp_error(int ret, t_main *main);
int						set_msg(int ret, char *msg, t_main *main);

/*
**	get_champ.c
*/
void					get_champ(char *file, t_main *main, const int index);

/*
**	free_all.c
*/
void					free_all(t_main *main);

/*
**	vm_utils.c
*/
void					init_vm(t_main *main);

/*
**	carriage_utils.c
*/
void					init_carriage(int nb_player, t_main *main);
t_carriage_lst			*add_carriage(t_carriage_lst *start,
						t_carriage carriage);

/*
**	declare_utils.c
*/
void					declare_champ(t_main *main, t_champ *champs,
						int nb_player);
int						declare_winner(t_main *main, int player_index);

/*
**	update_cycle.c
*/
void					update_cycle(t_main *main);

/*
**	exec_cycle.c
*/
void					exec_cycle(t_main *main);

/*
**	bytes_utils.c
*/
int						read_bytes(t_byte arr[], int index, int nb_bytes);
void					write_bytes(t_byte arr[], int index, int nb);

/*
**	spe_op.c
*/
void					live_op(t_args *args, t_main *main,
						t_carriage_lst *cge);
void					zjmp_op(t_args *args, t_main *main,
						t_carriage_lst *cge);
void					aff_op(t_args *args, t_main *main,
						t_carriage_lst *cge);

/*
**	mem_op.c
*/
void					ld_op(t_args *args, t_main *main, t_carriage_lst *cge);
void					st_op(t_args *args, t_main *main, t_carriage_lst *cge);
void					lld_op(t_args *args, t_main *main, t_carriage_lst *cge);

/*
**	op_op.c
*/
void					add_op(t_args *args, t_main *main, t_carriage_lst *cge);
void					sub_op(t_args *args, t_main *main, t_carriage_lst *cge);

/*
**	index_op.c
*/
void					ldi_op(t_args *args, t_main *main, t_carriage_lst *cge);
void					sti_op(t_args *args, t_main *main, t_carriage_lst *cge);
void					lldi_op(t_args *args, t_main *main,
						t_carriage_lst *cge);

/*
**	fork_op.c
*/
void					fork_op(t_args *args, t_main *main,
						t_carriage_lst *cge);
void					lfork_op(t_args *args, t_main *main,
						t_carriage_lst *cge);

/*
**	bitwise_op.c
*/
void					and_op(t_args *args, t_main *main, t_carriage_lst *cge);
void					or_op(t_args *args, t_main *main, t_carriage_lst *cge);
void					xor_op(t_args *args, t_main *main, t_carriage_lst *cge);

/*
**	bonus.c
*/
void					disp_op(t_main *main, char *op, t_carriage_lst *cge);
void					disp_new_carriage_state(t_main *main, int tot_cycle,
						int player,
						t_byte state);
void					disp_live(t_main *main, int tot_live);
void					set_colors(t_main *main, char *color);

/*
**	parse_bonus.c
*/
void					fill_option(t_main *main, char **av, int *i);
void					treat_n(t_main *main, char **av, int *i);
void					treat_dump(t_main *main, char **av, int *i);
void					treat_stop(t_main *main, char **av, int *i);

/*
**	sort_n.c
*/
void					sort_lst(t_main *main);

/*
**	disp_state.c
*/
void					disp_cge_and_stop(t_main *main);

/*
**	dump_memory.c
*/
void					dump_memory(t_main *main);
void					d_memory(t_main *main);

#endif
