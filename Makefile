# MINIRT_PROJECT_MAKEFILE
include libft/.make

NAME				:=	miniRT
CC					:=	cc
FLAGS				:=	-g -Wall -Wextra -Werror

# MINIRT
MINIRT_NAME			:=	main.c
MINIRT_PATH			:=	miniRT/
MINIRT				:=	$(addprefix $(MINIRT_PATH), $(MINIRT_NAME))

# SOURCE_FILES
SRCS				:=	$(MINIRT) 
SRCS_PATH			:=	srcs/

# OBJECT_FILES
OBJS_PATH			:=	objs/
OBJS				:=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))

# LIBFT_LIBRARY
LIBFT_PATH			:=	$(LIBFT_PATH)
LIBFT_SOURSES		:=	$(addprefix $(LIBFT_PATH), $(LIBFT_SOURSES))
LIBFT				:=	$(addprefix $(LIBFT_PATH), $(LIBFT))

# MLX42_LIBRARY
MLX_PATH			:=	MLX42/
LIBMLX				:=	$(MLX_PATH)build/libmlx42.a

# HEADERS AND EXTERNAL LIBRARIES
HEADERS				:=	$(LIBFT_PATH)libft.h
INCLUDES			:=	$(addprefix -I , $(HEADERS)) -I $(MLX_PATH)include
LIBS				:=	-L$(LIBFT_PATH) -lft -L$(MLX_PATH)build -lmlx42 -L"/Users/$(USER)/.brew/opt/glfw/lib" -lglfw -framework Cocoa -framework OpenGL -framework IOKit

# LOADING PROGRESS BAR INIT
TOTAL_OBJS			:= $(words $(OBJS))
COMPILED_OBJS		:= 0
MSG_PRINTED 		:= false

# RULES
all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS_PATH) $(OBJS) $(HEADERS)
	@cc $(FLAGS) $(INCLUDES) $(LIBS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)\n\n$(NAME) created successfully!$(EC)"

$(LIBMLX):
	@cmake $(MLX_PATH) -B $(MLX_PATH)build && make -C $(MLX_PATH)build -j4

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(OBJS_PATH)$(MINIRT_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@$(call progress,"miniRT")

$(LIBFT): $(LIBFT_SOURSES)
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@rm -rf $(MLX_PATH)/build
	@rm -rf $(OBJS_PATH)
	@echo "$(RED)*.o files removed!$(EC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)\nFull clean up completed successfully!$(EC)"

re: fclean all

.PHONY: all clean fclean re

# cmake ./lib/MLX42 -B ./lib/MLX42/build && make -C ./lib/MLX42/build -j4