NAME=		lib_nibbler_mlx.so
vpath %.cpp ./src/
SRC=	MlxLibFactory.cpp	\
	MlxLib.cpp
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

MLX=	libmlx.a

all:		$(MLX) $(NAME)

$(NAME):	$(OBJ)
		@printf "\t====> Linking %s...\n" $(NAME)
		$(CC) -shared -o $(NAME) $(OBJ) -lX11 -lXext -L. -lmlx

$(MLX):
		@printf "\t====> Compiling minilibx...\n"
		@+$(MAKE) -C ./minilibx/
		@cp ./minilibx/$(MLX) .

clean:
		@printf "Cleaning directory %s...\n" `pwd`
		$(RM) *~
		$(RM) \#*#
		$(RM) $(OBJ)
		@$(MAKE) clean -C ./minilibx/

fclean:		clean
		$(RM) $(NAME) $(MLX)

objs/%.o : %.cpp
		@printf "\t - CC %s\n" $<
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

re:		fclean \
		all
