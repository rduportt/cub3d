# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: votre_nom <votre_email@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 15:22:00 by user              #+#    #+#              #
#    Updated: 2025/02/17 15:22:00 by user             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -I./libft -I./get_next_line -I./minilibx-linux
MLX_FLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

# Fichiers sources principaux
SRCS = main.c \
       parsing.c parsing2.c parsing3.c parsing4.c parsing5.c \
       inputs.c inputs2.c \
       raycasting1.c raycasting2.c raycasting3.c \
       utils.c

# Fichiers de get_next_line
GNL_SRCS = get_next_line/get_next_line_bonus.c \
           get_next_line/get_next_line_utils_bonus.c

# Fichiers sources de la libft
LIBFT_SRCS = libft/ft_atoi.c \
             libft/ft_bzero.c \
             libft/ft_calloc.c \
             libft/ft_isalnum.c \
             libft/ft_isalpha.c \
             libft/ft_isascii.c \
             libft/ft_isdigit.c \
             libft/ft_isprint.c \
             libft/ft_itoa.c \
             libft/ft_memchr.c \
             libft/ft_memcmp.c \
             libft/ft_memcpy.c \
             libft/ft_memmove.c \
             libft/ft_memset.c \
             libft/ft_putchar_fd.c \
             libft/ft_putendl_fd.c \
             libft/ft_putnbr_fd.c \
             libft/ft_putstr_fd.c \
             libft/ft_split.c \
             libft/ft_strchr.c \
             libft/ft_strdup.c \
             libft/ft_striteri.c \
             libft/ft_strjoin.c \
             libft/ft_strlcat.c \
             libft/ft_strlcpy.c \
             libft/ft_strlen.c \
             libft/ft_strmapi.c \
             libft/ft_strncmp.c \
             libft/ft_strnstr.c \
             libft/ft_strrchr.c \
             libft/ft_strtrim.c \
             libft/ft_substr.c \
             libft/ft_tolower.c \
             libft/ft_toupper.c

# Tous les fichiers sources
ALL_SRCS = $(SRCS) $(GNL_SRCS)

# Fichiers objets
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(ALL_SRCS:.c=.o))
LIBFT_OBJS = $(addprefix $(OBJS_DIR)/libft/, $(notdir $(LIBFT_SRCS:.c=.o)))
LIBFT_A = libft/libft.a

# Règle principale
all: $(NAME)

# Création du dossier des objets
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/get_next_line
	mkdir -p $(OBJS_DIR)/libft

# Compilation de la libft
$(LIBFT_A): $(LIBFT_OBJS)
	ar rcs $(LIBFT_A) $(LIBFT_OBJS)

# Compilation des objets de la libft
$(OBJS_DIR)/libft/%.o: libft/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation des objets de get_next_line
$(OBJS_DIR)/get_next_line/%.o: get_next_line/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation des objets principaux
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation de la minilibx
mlx:
	make -C ./minilibx-linux

# Édition des liens
$(NAME): mlx $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) $(MLX_FLAGS)

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJS_DIR)
	make -C ./minilibx-linux clean

# Nettoyage complet
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_A)

# Reconstruction complète
re: fclean all

.PHONY: all clean fclean re mlx
.SECONDARY: $(OBJS) $(LIBFT_OBJS)