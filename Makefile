NAME =		pipex

CFLAGS =	-Wall -Wextra -Werror -I .

SFLAGS =	-fsanitize=address -g

CC =		gcc

LIBSDIR =	libft/

OBJS_DIR = .objs

OBJ =	$(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))

FILES = pipex.c									\
		parsing.c								\
		exec.c									\
		check.c									\

all: libs $(NAME)

libs:
	$(MAKE) -C $(LIBSDIR)

$(NAME): $(OBJ) $(LIBSDIR)libft.a
	$(CC) $(SFLAG) $(OBJ) $(LIBSDIR)libft.a -o $(NAME)
	
$(OBJS_DIR)/%.o:		%.c pipex.h ${LIBSDIR}libft.h ${LIBSDIR}libft.a Makefile
				mkdir -p $(dir $@)
				${CC} ${CFLAGS} -I$(LIBSDIR) -c $< -o $@

clean :
				${MAKE} clean -C ${LIBSDIR}
				rm -f ${OBJ} ${OBJ_B} $(OBJS_DIR)/*.o 

fclean :
				${MAKE} fclean -C ${LIBSDIR}
				rm -f ${OBJ} ${OBJ_B} $(OBJS_DIR)/*.o
				rm -f ${NAME}

re :			fclean all

.PHONY:			all clean fclean bonus libs re
