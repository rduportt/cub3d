# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_login <your_login@student.42.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/13 00:00:00 by your_login       #+#    #+#              #
#    Updated: 2026/02/13 00:00:00 by your_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

# Sources
SRCS        = parsing.c parsing2.c parsing3.c parsing4.c parsing5.c \
              main.c raycasting.c
OBJS        = $(SRCS:.c=.o)

# Directories
LIBFT_DIR   = libft
GNL_DIR     = get_next_line
MLX_DIR     = minilibx-linux

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

# Compilation flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -I. -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)
MLX_FLAG    = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -L$(LIBFT_DIR) -lft

# GNL files
GNL_SRCS    = $(GNL_DIR)/get_next_line_bonus.c \
              $(GNL_DIR)/get_next_line_utils_bonus.c
GNL_OBJS    = $(GNL_SRCS:.c=.o)

# Colors
GREEN       = \033[0;32m]
RED         = \033[0;31m]
YELLOW      = \033[0;33m]
RESET       = \033[0m]

# Rules
all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) $(LIBFT) $(MLX)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(MLX_FLAG) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft ready!$(RESET)"

$(MLX):
	@echo "$(GREEN)Building minilibx...$(RESET)"
	@make -C $(MLX_DIR)
	@echo "$(GREEN)✓ minilibx ready!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS) $(GNL_OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "$(RED)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executables and libraries...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)✓ All cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re