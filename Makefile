# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbenoit <cbenoit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 17:33:24 by coremart          #+#    #+#              #
#    Updated: 2019/11/01 00:02:31 by coremart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##COMPILATION ##
NAME  = corewar
EXEC = asm
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security \
-fsanitize=undefined
CFLAGS = -g -Werror -Wall -Wextra -std=c99 -pedantic-errors
DFLAGS = -MT $@ -MMD -MP -MF $(DDIR)/$*.d
AFLAGS =
ASAN =

## INCLUDES ##
LIB = libft
LIBH = $(LIB)/include
HDIR = include
LIBA = $(LIB)/libft.a

## SOURCES ##
SDIR = src
_SRCS = main.c disp_error.c free_all.c parse_input.c get_champ.c \
vm_utils.c carriage_utils.c declare_utils.c update_cycle.c exec_cycle.c \
bytes_utils.c disp_bonus.c bitwise_op.c parse_bonus.c spe_op.c mem_op.c index_op.c \
op_op.c fork_op.c sort_n.c disp_state.c dump_memory.c

_SRCS2 = main_asm.c ft_fill_header.c ft_asm.c ft_instructions.c	\
ft_add_instr.c ft_param.c ft_label.c ft_add_label.c	\
ft_fill_gap.c ft_write.c ft_fill_optab.c

## OBJECTS ##
ODIR = obj
_OBJS = $(_SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))
_OBJS2 = $(_SRCS2:.c=.o)
OBJS2 = $(patsubst %,$(ODIR)/%,$(_OBJS2))

## DEPENDENCIES ##
DDIR = dep
_DEPS = $(_OBJS:.o=.d)
DEPS = $(patsubst %,$(DDIR)/%,$(_DEPS))
_DEPS2 = $(_OBJS2:.o=.d)
DEPS2 = $(patsubst %,$(DDIR)/%,$(_DEPS2))

### RULES ###
all: $(NAME) $(EXEC) 

$(NAME): $(OBJS)
	@if [ "$(AFLAGS)" == "" ];\
	then\
		make -j 8 -C $(LIB);\
	else\
		make -j 8 -C $(LIB) asan;\
	fi
	clang -o $(NAME) $(LIBA) $(OBJS) $(CFLAGS) $(AFLAGS)
	
$(EXEC): $(OBJS2)
	@if [ "$(AFLAGS)" == "" ];\
	then\
		make -j 8 -C $(LIB);\
	else\
		make -j 8 -C $(LIB) asan;\
	fi
	clang -o $(EXEC) $(LIBA) $(OBJS2) $(CFLAGS) $(AFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c
	clang $(CFLAGS) $(DFLAGS) -o $@ -c $< -I $(HDIR) -I $(LIBH) $(AFLAGS)

-include $(DEPS)
-include $(DEPS2)

clean:
	@make -j 8 -C $(LIB) clean
	@rm -f $(OBJS)
	@rm -f $(OBJS2)

fclean: clean
	@make -j 8 -C $(LIB) fclean
	@rm -f $(NAME)
	@rm -f $(EXEC)
	@rm -rf $(NAME).dSYM
	@rm -rf $(EXEC).dSYM

re: fclean all

asan: AFLAGS = $(ASANFLAGS)
asan: all

reasan: AFLAGS = $(ASANFLAGS)
reasan: re

.PRECIOUS: $(DDIR)/%.d
.PHONY: all clean fclean re
