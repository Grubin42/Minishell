NAME = minishell

CC = gcc
CFLAGS = -Wextra -Werror -Wall #-g3 #-fsanitize=address
CFLAGS += -Ilibft -I$(HOME)/.brew/Cellar/readline/8.1.2/include
LDFLAGS += -Llibft -lreadline -L$(HOME)/.brew/Cellar/readline/8.1.2/lib

AR = ar -rc

SRCS_DIR = ./src
OBJS_DIR = ./objs
INC_DIR = .
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a


SRCS =	main.c \
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

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

vpath %.c $(SRCS_DIR)

RM = rm -f

.PHONY: all re clean fclean debug

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $^

debug: CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
debug: fclean $(NAME)

valgrind: CFLAGS += -g3
valgrind: fclean $(NAME)

clean :
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) -r $(OBJS_DIR)

fclean : clean
	@$(RM) $(NAME)

re : fclean all