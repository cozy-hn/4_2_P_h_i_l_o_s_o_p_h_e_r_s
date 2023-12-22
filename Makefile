CC = gcc
WFLAG = -Wall -Wextra -Werror
RMF = rm -f

MAN_DIR = ./man/
MAN_BASE = push_swap argv_parser cal_case command command_2 ft_split greedy list_ctl \
		pivot_check util
MAN_SRC = $(addprefix $(MAN_DIR), $(addsuffix .c, $(MAN_BASE)))
MAN_OBJ = $(addprefix $(MAN_DIR), $(addsuffix .o, $(MAN_BASE)))
NAME = push_swap

BON_DIR = ./bon/
BON_BASE = checker argv_parser command command_2 ft_split list_ctl util \
		gnl/get_next_line gnl/get_next_line_utils
BON_SRC = $(addprefix $(BON_DIR), $(addsuffix _bonus.c, $(BON_BASE)))
BON_OBJ = $(addprefix $(BON_DIR), $(addsuffix _bonus.o, $(BON_BASE)))
BON_NAME = checker

all : $(NAME)

$(NAME) : $(MAN_OBJ)
	@make re -j -C ./ft_printf
	$(CC) $(WFLAG) -Lft_printf -lftprintf $^ -o $@

bonus : $(BON_OBJ)
	$(CC) $(WFLAG) $^ -o $(BON_NAME)
	@touch bonus

%.o : %.c
	$(CC) $(WFLAG) -I $(dir $<) -c $< -o $@

clean :
	make clean -C ./ft_printf
	$(RMF) $(MAN_OBJ) $(BON_OBJ) bonus

fclean : clean
	$(RMF) $(NAME) $(BON_NAME) ./ft_printf/libftprintf.a

re : clean all

.PHONY : all clean fclean re

party :
	@printf "\033c"
	@echo "\n\033[35m♪┏(・o･)┛♪\n"
	@sleep 0.5
	@printf "\033c"
	@echo "\n\033[1;33m♪┗(・o･)┓♪\n"
	@sleep 0.5
	@printf "\033c"
	@echo "\n\033[36m♪┏(・o･)┛♪\n"
	@sleep 0.5
	@printf "\033c"
	@echo "\n\033[34m♪┗(・o･)┓♪\n"