# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:55:16 by itan              #+#    #+#              #
#    Updated: 2023/03/10 21:00:41 by itan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

SRC_DIR	= src
OBJ_DIR	= obj

# this is for mirroring the out dir
OBJ_DIRS= $(subst $(SRC_DIR), $(OBJ_DIR), $(shell find src -type d))

SRC		= $(shell find $(SRC_DIR) -name '*.c')
OBJ		= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

AR		= ar -rcs
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f
INC		= $(addprefix -I , $(shell find includes -type d -name includes))

LIBDIR	= includes/libft
LIB		= -L$(LIBDIR) -lft
LIBNAME	= libft.a
# this is for debugging
DNAME	= debug.out
# DDIR	= test
DFLAGS	= -fsanitize=address -fdiagnostics-color=always -g3
# DSRC	= $(shell find $(DDIR) -name '*.c')
DOBJ	= $(DSRC:.c=.o)

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
MLXLIB	= -I /usr/local/include -L/usr/local/lib -lbsd -lmlx -lXext -lX11
endif
ifeq ($(UNAME), Darwin)
INC += -I /usr/local/include 
MLXLIB	= -I /usr/local/include -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
endif


# ** COLORS ** #
BLACK		= \033[30m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
MAGENTA		= \033[35m
CYAN		= \033[36m
WHITE		= \033[37m
B_BLACK		= \033[40m
B_RED		= \033[41m
B_GREEN		= \033[42m
B_YELLOW	= \033[43m
B_BLUE		= \033[44m
B_MAGENTA	= \033[45m
B_CYAN		= \033[46m
B_WHITE		= \033[47m
BRIGHT		= \033[1m
NORMAL		= \033[0m
BLINK		= \033[4m
REVERSE		= \033[5m
UNDERLINE	= \033[3m

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@mkdir -p $(OBJ_DIRS)
				@printf "$(YELLOW)$(BRIGHT)Generating %25s\t$(NORMAL)%40s\r" "$(NAME) src objects..." $@
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DDIR)/%.o:	$(DDIR)/%.c
				@mkdir -p $(DDIR)
				@printf "$(YELLOW)$(BRIGHT)Generating %25s\t$(NORMAL)%40s\r" "$(NAME) debug objects..." $@
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME)::	$(LIBDIR)/$(LIBNAME) $(OBJ) 
			@printf "\n$(MAGENTA)$(BRIGHT)Compiling $(NAME)...          \n"
			@$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME) $(LIB) $(MLXLIB)
			@printf "$(GREEN)COMPLETE!!\n\n"

$(DNAME):	$(SRC) $(DSRC) $(LIBDIR)/$(LIBNAME)
			@printf "\n$(MAGENTA)Compiling $(DNAME) for $(NAME)...          \n"
			@$(CC) $(CFLAGS) $(DFLAGS) $(INC) $(SRC) $(DSRC) -o $(DNAME) $(LIB) $(MLXLIB)
			@printf "$(GREEN)COMPLETE!!\n\n"

$(LIBDIR)/$(LIBNAME):
		@make -C $(LIBDIR) --no-print-directory

debug:	$(DNAME)

all:	$(NAME)

clean:
		@printf "$(RED)$(BRIGHT)Removing $(NAME) objects...\n$(NORMAL)"
		@make clean -C $(LIBDIR) --no-print-directory
		@$(RM) $(OBJ) $(DOBJ)
		@$(RM) -r $(OBJ_DIR)

fclean:	clean
		@printf "$(RED)$(BRIGHT)Deleting $(NAME) and $(DNAME)...\n\n$(NORMAL)"
		@make fclean -C $(LIBDIR) --no-print-directory
		@$(RM) $(NAME)
		@$(RM) $(DNAME)

re:			fclean all

.PHONY: all clean fclean re debug bonus norm

norm:
		@norminette $(SRC_DIR) includes/