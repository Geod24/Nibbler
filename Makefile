NAME=	nibbler
vpath %.cpp ./src/
SRC=	main.cpp		\
	NibblerSnake.cpp	\
	NibblerCore.cpp
OBJ=	$(patsubst %.cpp,objs/%.o,$(SRC))

# Configuring Makefile & output options
MAKEFLAGS+=	-rR --no-print-directory

# Compilation data
CXXFLAGS=	-W -Wall $(EXTRA_FLAGS) -std=c++0x -g
EXTRA_FLAGS=	-Wfloat-equal
INCLUDES=	-I includes/

# Platform data
RM=	@rm -rf
CC=	@g++

all:		$(NAME) libs

$(NAME):	$(OBJ)
		@printf "\t====> Linking %s...\n" $(NAME)
		$(CC) -o $(NAME) $(OBJ) -ldl

####################### LIBS #################################
LIB_NCURSES=	lib_nibbler_ncurses.so
LIB_SDL=	lib_nibbler_sdl.so
LIB_MLX=	lib_nibbler_mlx.so

libs:	$(LIB_NCURSES) $(LIB_SDL) $(LIB_MLX)

$(LIB_NCURSES):
		@+$(MAKE) -C ./libs/ncurses_lib/
		@cp -rf ./libs/ncurses_lib/$(LIB_NCURSES) .

$(LIB_SDL):
		@+$(MAKE) -C ./libs/SDL_lib/
		@cp -rf ./libs/SDL_lib/$(LIB_SDL) .

$(LIB_MLX):
		@+$(MAKE) -C ./libs/mlx_lib/
		@cp -rf ./libs/mlx_lib/$(LIB_MLX) .

####################### LIBS #################################


clean:
		@printf "Cleaning directory %s...\n" `pwd`
		$(RM) *~
		$(RM) \#*#
		$(RM) $(OBJ) $(TOBJ)
		@+$(MAKE) clean -C ./libs/ncurses_lib/
		@+$(MAKE) clean -C ./libs/SDL_lib/
		@+$(MAKE) clean -C ./libs/mlx_lib/

fclean:		clean
		$(RM) $(NAME) $(TNAME) $(LIB_NCURSES) $(LIB_MLX) $(LIB_SDL)
		@+$(MAKE) fclean -C ./libs/ncurses_lib/
		@+$(MAKE) fclean -C ./libs/SDL_lib/
		@+$(MAKE) fclean -C ./libs/mlx_lib/

objs/%.o : %.cpp
		@printf "\t - CC %s\n" $<
		$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

re:		fclean \
                all

.PHONY: re fclean clean libs
.NOTPARALLEL: all
