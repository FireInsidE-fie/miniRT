NAME		=	miniRT
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm
RMFLAGS		=	-f

SRCDIR		=	./src
CFILES		=	$(SRCDIR)/minirt.c

OBJS		=	$(CFILES:.c=.o)

INCLDIR		=	include
IFILES		=	$(INCLDIR)/minirt.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

# TODO - Add mlx compilation

LIBS		=	-L$(LIBFT_DIR) -lft -lreadline

VALGRIND	=	valgrind
VALFLAGS	=	--leak-check=full --track-fds=yes
LOG			=	valgrind.log


all:			$(NAME)

# Build libft first
$(LIBFT):
				@printf "\rCompiling libft"
				@make -C $(LIBFT_DIR) --no-print-directory
				@printf "\rCompiled libft successfully.\n"

# Compile object files
%.o:			%.c $(IFILES)
				@printf "\rCompiling $<..."
				@$(CC) $(CFLAGS) -I$(INCLDIR) -I$(LIBFT_DIR) -c $< -o $@

# Compile project with the existing libs
$(NAME):		$(OBJS) $(LIBFT)
				@printf "\rCompiling $(NAME)..."
				@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
				@printf "\r\n\033[32m$(NAME) compiled.\033[0m\n"
clean:
				@printf "\rCleaning object files"
				@$(RM) $(RMFLAGS) $(OBJS)
				@make clean -C $(LIBFT_DIR)/ --no-print-directory
				@printf "\rObject files cleaned.\n"

fclean:			clean
				@printf "\rRemoving $(NAME)..."
				@$(RM) $(RMFLAGS) $(NAME)
				@make fclean -C $(LIBFT_DIR)/ --no-print-directory
				@printf "\r$(NAME) Removed.\n"

re:				fclean all

test:			$(NAME)
				@printf "\n===============================================================\n"
				$(VALGRIND) $(VALFLAGS) ./$(NAME) 2>> $(LOG)

.PHONY:			all clean fclean re test
