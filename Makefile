MAIN            =       main.c

SRC             =       polynomials.c

SRCTEST         =       tests/unit_tests.c

OBJ             =       $(SRC:.c=.o)

NAME            =       example

NAMETESTS       =       unit_tests

NAMEDEBUG       =       debug

RM              +=      -r

CC              =       gcc

CFLAGS          +=      -W -Wall -Wextra

CPPFLAGS        +=      -I include/

CFLAGSTEST      =       -coverage -lcriterion

CFLAGSDEBUG     =       -g3

LDFLAGS	        +=      -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(MAIN) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) */*.gcda
	$(RM) */*.gcno

fclean: clean
	$(RM) $(NAME) $(NAMETESTS) $(NAMEDEBUG)

re:	fclean all

tests_run:
	$(CC) -o $(NAMETESTS) $(SRC) $(SRCTEST) $(CFLAGS) $(CPPFLAGS) $(CFLAGSTEST) $(LDFLAGS)
	./$(NAMETESTS)
	gcovr -e $(SRCTEST)

debug:
	$(CC) -o $(NAMEDEBUG) $(MAIN) $(SRC) $(CFLAGS) $(CFLAGSDEBUG) $(CPPFLAGS) $(LDFLAGS)

.PHONY:	all clean fclean re tests_run debug
