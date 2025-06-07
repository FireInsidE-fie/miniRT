NAME		=	miniRT
CC			=	cc
CFLAGS		=	-Wall -Wextra -Wpedantic -Werror -g
RM			=	rm
RMFLAGS		=	-f

SRCDIR		=	./src
CFILES		=	$(SRCDIR)/minirt.c \
				$(SRCDIR)/mlx.c \
				$(SRCDIR)/point3.c \
				$(SRCDIR)/scene/scene.c \
				$(SRCDIR)/scene/ambient.c \
				$(SRCDIR)/scene/camera.c \
				$(SRCDIR)/scene/color.c \
				$(SRCDIR)/scene/cylinder.c \
				$(SRCDIR)/scene/light.c \
				$(SRCDIR)/scene/plane.c \
				$(SRCDIR)/scene/sphere.c \

OBJS		=	$(CFILES:.c=.o)

INCLDIR		=	include
IFILES		=	$(INCLDIR)/minirt.h \
				$(INCLDIR)/scene.h \
				$(INCLDIR)/ambient.h \
				$(INCLDIR)/camera.h \
				$(INCLDIR)/color.h \
				$(INCLDIR)/cylinder.h \
				$(INCLDIR)/light.h \
				$(INCLDIR)/plane.h \
				$(INCLDIR)/sphere.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

MLX_DIR		=	./mlx
MLX			=	$(MLX_DIR)/libmlx.a

LIBS		=	-L$(LIBFT_DIR) -L$(MLX_DIR) -lft -lm -lmlx -lXext -lX11

VALGRIND	=	valgrind
VALFLAGS	=	--leak-check=full --track-fds=yes --show-leak-kinds=all
LOG			=	valgrind.log


all:			$(NAME)

$(LIBFT):
				@printf "\rCompiling libft..."
				@make -C $(LIBFT_DIR) --no-print-directory
				@printf "\r[!] - Successfully compiled libft!\n"

$(MLX):
				@printf "\rCompiling MLX..."
				@make -C $(MLX_DIR) --no-print-directory
				@printf "\r[!] - Successfully compiled MLX!\n"

# Compile object files
%.o:			%.c $(IFILES)
				@printf "\rCompiling $<..."
				@$(CC) $(CFLAGS) -I$(INCLDIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# Build project with the libraries used
$(NAME):		$(OBJS) $(LIBFT) $(MLX)
				@printf "\rCompiling $(NAME)..."
				@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
				@printf "\r\n\033[32m$(NAME) compiled.\033[0m\n"

clean:
				@printf "\rCleaning object files"
				@$(RM) $(RMFLAGS) $(OBJS)
				@$(RM) $(RMFLAGS) $(LOG)
				@make clean -C $(LIBFT_DIR)/ --no-print-directory
				@make clean -C $(MLX_DIR) --no-print-directory
				@printf "\rObject files cleaned.\n"

fclean:			clean
				@printf "\rRemoving $(NAME)..."
				@$(RM) $(RMFLAGS) $(NAME)
				@make fclean -C $(LIBFT_DIR) --no-print-directory
				@printf "\r$(NAME) Removed.\n"

re:				fclean all

# Automated test suite
test:			$(NAME)
				@$(RM) $(RMFLAGS) $(LOG)
				@printf "[!] - Launching test suite..."
				@printf "\n===============================================================\n"
				$(VALGRIND) $(VALFLAGS) ./$(NAME) 2>> $(LOG)

# 42 Norm checks
check:
				@norminette src/ include/

.PHONY:			all clean fclean re test check
