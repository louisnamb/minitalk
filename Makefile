# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/21 15:46:52 by lnambaji          #+#    #+#              #
#    Updated: 2023/06/22 12:14:25 by lnambaji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CNAME			=	client

SNAME			=	server

SRCS_SERVER		=	server.c libft/ft_atoi.c libft/ft_memset.c \
            	printf/ft_printf.c printf/ft_strlen.c \
				printf/hexchars.c printf/putchars.c

SRCS_CLIENT		=	client.c libft/ft_atoi.c libft/ft_memset.c \
				printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c \
				printf/putchars.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

LIB_SRCS		=	libft/ft_atoi.c libft/ft_memset.c

PRINT_SRCS		=	printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c \
				printf/putchars.c
OBJS		=	$(LIB_SRCS:.c=.o) $(PRINT_SRCS:.c=.o) $(OBJS_CLIENT) $(OBJS_SERVER)

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

CC			=	gcc

all: $(SNAME) $(CNAME)

%.o: %.c
	$(CC) -g $(FLAGS) -c $< -o $@

$(CNAME): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(CNAME) $(OBJS_CLIENT)

$(SNAME): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(SNAME) $(OBJS_SERVER)

clean:
	$(RM) $(OBJS) $()

fclean: clean
	$(RM) $(CNAME) $(SNAME)

re: fclean all

.PHONY:	all clean fclean re