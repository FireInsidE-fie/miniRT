NAME		=	miniRT
CC			=	cc
CFLAGS		=	-Wall -Wextra -Wpedantic -Werror -g
RM			=	rm
RMFLAGS		=	-f

SRCDIR		=	./src
CFILES		=	$(SRCDIR)/minirt.c \
				$(SRCDIR)/mlx.c \
				$(SRCDIR)/render.c \
				$(SRCDIR)/fast_render.c \
				$(SRCDIR)/utils/point3.c \
				$(SRCDIR)/utils/utils.c \
				$(SRCDIR)/utils/vector.c \
				$(SRCDIR)/scene/ambient.c \
				$(SRCDIR)/scene/camera.c \
				$(SRCDIR)/scene/material.c \
				$(SRCDIR)/scene/light.c \
				$(SRCDIR)/scene/scene.c \
				$(SRCDIR)/scene/sphere.c \
				$(SRCDIR)/scene/plane.c \
				$(SRCDIR)/scene/cylinder.c \
				$(SRCDIR)/scene/cone.c \
				$(SRCDIR)/scene/cylinder_utils.c \
				$(SRCDIR)/scene/cone_utils.c \
				$(SRCDIR)/hierarchy/hierarchy.c \
				$(SRCDIR)/hierarchy/ewin.c \
				$(SRCDIR)/hierarchy/ewin_sphere.c \
				$(SRCDIR)/hierarchy/ewin_plane.c \
				$(SRCDIR)/hierarchy/ewin_cylinder.c \
				$(SRCDIR)/hierarchy/ewin_cylinder_utils.c \
				$(SRCDIR)/hierarchy/color_picker.c \
				$(SRCDIR)/hierarchy/hierarchy_utils.c \
				$(SRCDIR)/lighting/lighting.c \
				$(SRCDIR)/lighting/reflections.c \
				$(SRCDIR)/parsing/parsing.c \
				$(SRCDIR)/parsing/parsing_metas.c \
				$(SRCDIR)/parsing/parsing_shapes.c \
				$(SRCDIR)/parsing/parsing_utils.c \
				$(SRCDIR)/movement/camera_movement.c \
				$(SRCDIR)/movement/camera_rotation.c \
				$(SRCDIR)/textures/sphere_textures.c \
				$(SRCDIR)/textures/sphere_bump.c \
				$(SRCDIR)/textures/checkerboard.c \

OBJS		=	$(CFILES:.c=.o)

INCLDIR		=	include
IFILES		=	$(INCLDIR)/minirt.h \
				$(INCLDIR)/ambient.h \
				$(INCLDIR)/camera.h \
				$(INCLDIR)/light.h \
				$(INCLDIR)/material.h \
				$(INCLDIR)/sphere.h \
				$(INCLDIR)/cylinder.h \
				$(INCLDIR)/plane.h \
				$(INCLDIR)/cone.h \
				$(INCLDIR)/scene.h \
				$(INCLDIR)/utils.h \
				$(INCLDIR)/hierarchy.h \
				$(INCLDIR)/movement.h \
				$(INCLDIR)/textures.h \
				$(INCLDIR)/texturedata.h \
				$(INCLDIR)/vector.h

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
				@printf "[!] - Launching test suite..."
				@printf "\n==========================================================\n"
				$(VALGRIND) $(VALFLAGS) ./$(NAME) maps/valid1.rt 2>&1 | tee $(LOG)

# 42 Norm checks
check:
				@norminette src/ include/ | grep -v "42 header"

.PHONY:			all clean fclean re test check
