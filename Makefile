# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: <your_login> <your_email>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/XX/XX XX:XX:XX by <login>          #+#    #+#              #
#    Updated: 2024/XX/XX XX:XX:XX by <login>         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

# Sources
SRCS		= parsing.c

OBJS		= $(SRCS:.c=.o)

# Directories
LIBFT_DIR	= libft
GNL_DIR		= get_next_line

# Libraries
LIBFT		= $(LIBFT_DIR)/libft.a

# Compilation flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I. -I$(LIBFT_DIR) -I$(GNL_DIR)

# GNL files
GNL_SRCS	= $(GNL_DIR)/get_next_line_bonus.c \
			  $(GNL_DIR)/get_next_line_utils_bonus.c
GNL_OBJS	= $(GNL_SRCS:.c=.o)

# Colors
GREEN		= \033[0;32m]
RED			= \033[0;31m]
RESET		= \033[0m]

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) $(LIBFT)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft ready!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(O)