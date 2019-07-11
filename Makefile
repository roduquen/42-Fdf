CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = fdf
SRCDIR = ./
INCLDIR = ./includes/
ADDMLX = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit
LIBDIR = ./libft/
LIB = $(LIBDIR)libft.a
SRCS = $(SRCDIR)main.c \
	$(SRCDIR)data_initialisation.c \
	$(SRCDIR)mlx_init_and_leave.c \
	$(SRCDIR)destroy_list.c \
	$(SRCDIR)translate_file_to_list.c \
	$(SRCDIR)translate_point.c \
	$(SRCDIR)calcul_rotation_point.c \
	$(SRCDIR)draw_line.c \
	$(SRCDIR)draw_on_renderer.c \
	$(SRCDIR)commands_rotation.c \
	$(SRCDIR)render_draw_line.c \
	$(SRCDIR)commands.c \
	$(SRCDIR)commands_relief_and_zoom.c
OBJS_ = $(SRCS:.c=.o)
OBJS = $(notdir $(OBJS_))

all : $(LIB) $(NAME)

$(NAME) : $(SRCS)
	@make objects
	@$(CC) $(CFLAGS) -I $(INCLDIR) $^ -o $@ -L $(LIBDIR) -lft $(ADDMLX)
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

objects : $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $^ -I $(INCLDIR)
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

$(LIB) :
	@echo "\n\033[36mLibs Compilation :\033[0m \033[33m$(LIBDIR)\033[0m\n"
	@make -C libft

clean :
	@rm -rf $(OBJS)
	@echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"

fclean : clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"

re : fclean all

.PHONY : all clean fclean re objects
