NAME=		lib_nibbler_ncurses.so
vpath %.cpp ./src/
SRC=	NCurseLibFactory.cpp	\
	NCurseLib.cpp
OBJ=	$(patsubst %.cpp,objs/%.o,$(SRC))

# Configuring Makefile & output options
MAKEFLAGS+=	-rR --no-print-directory

# Compilation data
CFLAGS=	-Wextra -Wall -fPIC $(EXTRA_FLAGS) $(DEBUG_FLAGS) -g -std=c++0x
EXTRA_FLAGS=	-Wpacked -Wfloat-equal
DEBUG_FLAGS=	-g
INCLUDES=	-I includes/ -I ../../includes/

# Platform data
RM=	@rm -rf
CC=	@g++

$(NAME):	$(OBJ)
		@printf "\t====> Linking %s...\n" $(NAME)
		$(CC) -shared -lncurses -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
		@printf "Cleaning directory %s...\n" `pwd`
		$(RM) *~
		$(RM) \#*#
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

objs/%.o : %.cpp
		@printf "\t - CC %s\n" $<
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

re:		fclean \
		all
