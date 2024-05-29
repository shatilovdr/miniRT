# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 17:31:32 by ivalimak          #+#    #+#              #
#    Updated: 2024/05/27 23:23:58 by ivalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT

BUILD	:=	normal

SRCDIR	:=	srcs
OBJDIR	:=	objs
INCDIR	:=	inc
LFTDIR	:=	libft
MLXDIR	:=	MLX42

INCLUDE	:=	-I$(INCDIR) -I$(LFTDIR)/$(INCDIR) -I$(MLXDIR)/include

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

MINIRTDIR	:=	miniRT

MINIRTFILES	:=	main.c \
				element.c \
				error.c \
				file.c \
				object.c \
				parse_utils.c

FILES	:=	$(addprefix $(MINIRTDIR)/, $(MINIRTFILES))

SRCS	:=	$(addprefix $(SRCDIR)/, $(FILES))
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
	@mkdir -p $(OBJDIR)/$(MINIRTDIR)

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
