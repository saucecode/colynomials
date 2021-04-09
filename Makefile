MAIN		=	main.c

SRC		=	polynomials.c

SRCTEST		=	tests/unit_tests.c

OBJ		=	$(SRC:.c=.o)

NAME		=	example

RM		+=	-r

CC		=	gcc

CFLAGS		+=	-W -Wall -Wextra

CPPFLAGS	+=	-I include/

CFLAGSTEST	=	-coverage -lcriterion

LDFLAGS		+=	-lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(MAIN) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) *~
	$(RM) */*~
	$(RM) *.gc*
	$(RM) */*.gc*
	$(RM) vgcore.*

fclean: clean
	$(RM) $(NAME)
	$(RM) unit_tests

re:	fclean all

tests_run:
	$(CC) -o unit_tests $(SRC) $(SRCTEST) $(CFLAGSTEST) $(LDFLAGS)
	./unit_tests
	gcovr -e $(SRCTEST)

.PHONY:	all clean fclean re tests_run
