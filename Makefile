NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -DGL_SILENCE_DEPRECATION

MLX_DIR = ./others/minilibx
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./include
GNL_DIR = ./others/get_next_line
PRN_DIR = ./others/printf

MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
INCLUDES = -I$(MLX_DIR) -I$(INC_DIR) -I$(GNL_DIR) -I$(PRN_DIR)

SRC_FILES = main.c utils.c map.c sprite.c moves.c enemy.c \
            refactor.c refactor2.c get_next_line.c get_next_line_utils.c \
            ft_printf.c ft_printf_utils.c ft_printf_hex.c

SRCS = $(addprefix $(SRC_DIR)/,main.c utils.c map.c sprite.c moves.c enemy.c \
        refactor.c refactor2.c) \
       $(addprefix $(GNL_DIR)/,get_next_line.c get_next_line_utils.c) \
       $(addprefix $(PRN_DIR)/,ft_printf.c ft_printf_utils.c ft_printf_hex.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(GNL_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(PRN_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(MLX_DIR)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(PRN_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
