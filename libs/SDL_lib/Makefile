NAME=		lib_nibbler_sdl.so
vpath %.cpp ./src/
SRC=	SDLLib.cpp		\
	SDLLibFactory.cpp
OBJ=	$(patsubst %.cpp,objs/%.o,$(SRC))

# Configuring Makefile & output options
MAKEFLAGS+=	-rR --no-print-directory

# Compilation data
CXXFLAGS=	-Wextra -Wall -fPIC $(EXTRA_FLAGS) -std=c++0x
EXTRA_FLAGS=	-Wpacked -Wfloat-equal
DEBUG_FLAGS=	-g
INCLUDES=	-I includes/ -I ../../includes/

# Platform data
RM=	@rm -rf
CC=	@g++

$(NAME):	$(OBJ)
		@printf "\t====> Linking %s...\n" $(NAME)
		$(CC) -shared -lSDL -o $(NAME) $(OBJ)

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
		$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

re:		fclean \
		all
