# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 17:31:32 by ivalimak          #+#    #+#              #
#    Updated: 2024/07/22 16:59:07 by ivalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT

BUILD	:=	normal

SRCDIR	:=	srcs
OBJDIR	:=	objs
INCDIR	:=	inc
LFTDIR	:=	libft
MLXDIR	:=	MLX42

INCLUDE	:=	-I$(INCDIR) -I$(LFTDIR)/$(INCDIR) -I$(MLXDIR)/include/MLX42

CC				:=	cc
cflags.common	:=	-Wall -Wextra -Werror
cflags.debug	:=	-g
cflags.asan		:=	$(cflags.debug) -fsanitize=address
cflags.normal	:=	-Ofast
cflags.extra	:=	
CFLAGS			:=	$(cflags.common) $(cflags.$(BUILD)) $(cflags.extra) $(INCLUDE)

ifeq ($(shell uname),Linux)
	LDFLAGS	:=	-L$(LFTDIR) -L$(MLXDIR)/build -lft -lmlx42 -ldl -lglfw -pthread -lm
else
	LDFLAGS	:=	-L$(LFTDIR) -L$(MLXDIR)/build -L"/Users/$(USER)/.brew/opt/glfw/lib" -lft -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif


PARSER_NAME		:=	element.c \
					error.c \
					file.c \
					object.c \
					file_utils.c \
					parse_utils.c
PARSER_PATH		:=	parser
PARSER			:=	$(addprefix $(PARSER_PATH)/, $(PARSER_NAME))

LIN_ALG_NAME	:=	vec3_operations.c \
					vec3_operations2.c \
					vec3_multiplication.c \
					vec3_rotation.c
LIN_ALG_PATH	:=	lin_alg
LIN_ALG			:=	$(addprefix $(LIN_ALG_PATH)/, $(LIN_ALG_NAME))

SRCS	:=	$(addprefix $(SRCDIR)/, main.c) $(addprefix $(SRCDIR)/, $(PARSER)) $(addprefix $(SRCDIR)/, $(LIN_ALG))
OBJS	:=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

LFT		:=	$(LFTDIR)/libft.a
MLX42	:=	$(MLXDIR)/build/libmlx42.a

all: $(NAME)

$(NAME): $(MLX42) $(LFT) $(OBJDIR) $(OBJS)
	@printf "\e[32;1mMINIRT >\e[m Compiling %s\n" $@
	@cc $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	@printf "\e[32;1mMINIRT >\e[m \e[1mDone!\e[m\n"

$(MLX42):
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -j4 --no-print-directory -C $(MLXDIR)/build

$(LFT):
	@make --no-print-directory -C $(LFTDIR) BUILD=$(BUILD) cflags.extra=$(cflags.extra)

$(OBJDIR):
	@printf "\e[32;1mMINIRT >\e[m Creating objdir\n"
	@mkdir -p $(OBJDIR)/$(PARSER_PATH)
	@mkdir -p $(OBJDIR)/$(LIN_ALG_PATH)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[32;1mMINIRT >\e[m Compiling %s\n" $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make --no-print-directory -C $(LFTDIR) clean
	@rm -rf $(MLXDIR)/build
	@rm -f $(OBJS)

fclean: clean
	@make --no-print-directory -C $(LFTDIR) fclean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# cmake ./lib/MLX42 -B ./lib/MLX42/build && make -C ./lib/MLX42/build -j4
