# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grubin <grubin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 13:48:52 by grubin            #+#    #+#              #
#    Updated: 2022/06/09 14:51:30 by grubin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wextra -Werror -Wall #-fsanitize=address -g3
CFLAGS += -I ~/.brew/Cellar/readline/8.1.2/include -lreadline -L ~/.brew/Cellar/readline/8.1.2/lib
CFLAGS += -I ./libft/libft.h -lft -L ./libft
CFLAGS += -o minishell

AR = ar -rc

SRCS_DIR = ./src
OBJS_DIR = ./objs
INC_DIR = .
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a


SRCS = 	main.c \
		utils_quote.c \
		prompt_quote.c \
		chunck.c \
		init_data.c \
		utils_chunck.c \
		chunck_bis.c \
		init_cmd.c \
		chunk_quote.c \
		exec_cmd.c \
		dollar.c \
		check_builtins.c \
		execve.c \
		dollar_utils.c \
		builtin_cd.c \
		builtin_cd_utils.c \
		builtin_env.c \
		builtin_echo.c \
		builtin_unset.c \
		builtin_pwd.c \
		builtin_exit.c \
		builtin_export.c \
		signal.c \
		
#OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

vpath %.c $(SRCS_DIR)

RM = rm -f

all : $(NAME)


$(NAME) : $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS)
$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR)

#$(OBJS_DIR) :
#	@mkdir -p $(OBJS_DIR)

#$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
#	@$(CC) $(CFLAGS) -o $@ -I $(INC_DIR) -I$(LIBFT_DIR) -c $^

debug: $(LIBFT)
    @gcc $(CFLAGS) -fsanitize=address -g3 $(SRCS)

clean :
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) -r $(OBJS_DIR)

fclean : clean
	@$(RM) $(NAME)

re : fclean all