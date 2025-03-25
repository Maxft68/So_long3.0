# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 22:35:59 by mdsiurds          #+#    #+#              #
#    Updated: 2025/03/25 17:00:13 by mdsiurds         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRC = so_long.c
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = ./temp
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT_DIR = ./libft
LIBFT_LIB = ./libft/libft.a

# MLX42 configuration
MLX42_DIR = ./MLX42
MLX42_BUILD = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a
MLX42_INC = -I$(MLX42_DIR)/include
MLX42_FLAGS = -lXext -lm -lX11 -lglfw

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB) $(MLX42_LIB)
		@echo "Compiling so_long..."
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX42_LIB) $(MLX42_FLAGS) -o $(NAME)
		@echo "So_long successfully compiled.\n"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(MLX42_INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_LIB): 
	@echo	"Compiling libft..."
	@make -C $(LIBFT_DIR) >/dev/null 2>&1
	@echo "Libft successfully compiled."

$(MLX42_LIB):
	@echo "Compiling MLX42..."
	@mkdir -p $(MLX42_BUILD)
	@cd $(MLX42_DIR) && cmake -B build >/dev/null 2>&1
	@cd $(MLX42_DIR) && cmake --build build -j4 >/dev/null 2>&1
	@echo "MLX42 successfully compiled."

clean:
	@echo	"Cleaning..."
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@rm -rf $(MLX42_BUILD)
	@echo	"Successfully cleaned !\n"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	@rm -f $(OBJ)
	
re: fclean all

.PHONY: all clean fclean re