NAME		= philo

SRC			=	ft_printf/ft_display.c\
				ft_printf/ft_display2.c\
				ft_printf/ft_printf.c\
				main.c

SRCSPATH 	= srcs

INCLUDES	= ./includes/

OBJDIR		= all_o

CC			= gcc

CFLAGS		= -Werror -Wall -Wextra -pthread

RM			= rm -rf

SRCS = $(addprefix $(SRCSPATH)/,$(SRC))

OBJS        = $(addprefix $(OBJDIR)/,${SRC:.c=.o})

$(OBJDIR)/%.o: $(SRCSPATH)/%.c
	@printf "$(_ORANGE)Compiling : %s\n" $<
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/ft_printf
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

all: ${NAME}

${NAME}:	${OBJS}
	@${CC} ${CFLAGS} -I $(INCLUDES) ${OBJS} -o ${NAME}
	@printf "$(_GREEN)Compiling DONE !\n"

clean:
	@printf "$(_RED)Removing objects...\n"
	@${RM} ${OBJS} ./all_o/*.o

fclean:	clean
	@printf "$(_RED)Removing $(NAME)...\n"
	@${RM} ${NAME} ./all_o/*.o all_o

re:	fclean all

################################################# colors

_WHITE = \e[97m
_GREEN = \e[38;5;118m
_ORANGE = \e[38;5;208m
_RED = \e[38;5;196m
_R = \e[0m

#################################################

.PHONY: all clean fclean re
