##
## Makefile for MiniLibX in /home/boulon/work/c/raytraceur/minilibx
## 
## Made by Olivier Crouzet
## Login   <ol@epitech.net>
## 
## Started on  Tue Oct  5 15:56:43 2004 Olivier Crouzet
## Last update Sun Mar 18 22:11:53 2012 mathias lang
##

CC	= @gcc
RM	= @rm -rf
CFLAGS	= -w -Wall -I/usr/X11R6/include -O3 -fPIC

MAKEFLAGS+=	-rR --no-print-directory

NAME	= libmlx.a
vpath %.c ./src/
SRC	= mlx_init.c			\
	mlx_new_window.c		\
	mlx_pixel_put.c			\
	mlx_loop.c			\
	mlx_mouse_hook.c		\
	mlx_key_hook.c			\
	mlx_expose_hook.c		\
	mlx_loop_hook.c			\
	mlx_int_anti_resize_win.c	\
	mlx_int_do_nothing.c		\
	mlx_int_wait_first_expose.c	\
	mlx_int_get_visual.c		\
	mlx_flush_event.c		\
	mlx_string_put.c		\
	mlx_new_image.c			\
	mlx_get_data_addr.c		\
	mlx_put_image_to_window.c	\
	mlx_get_color_value.c		\
	mlx_clear_window.c		\
	mlx_xpm.c			\
	mlx_int_str_to_wordtab.c	\
	mlx_destroy_window.c		\
	mlx_int_param_event.c		\
	mlx_int_set_win_event_mask.c	\
	mlx_hook.c			\
	mlx_rgb.c			\
	mlx_nonblocking_loop.c

OBJ=	$(patsubst %.c,objs/%.o,$(SRC))
INCLUDES=	-I ./includes/

all:	$(NAME)

$(NAME):	$(OBJ)
	@printf "\t====> Linking %s...\n" $(NAME)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	@printf "Cleaning directory %s...\n" `pwd`
	$(RM) $(OBJ) $(NAME) *~ core *.core

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

objs/%.o : %.c
		@printf "\t - CC %s\n" $<
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
