SRCS 	= main.c utils.c handle_args.c
OBJS 	= $(SRCS:.c=.o)
CC	 	= cc
RM 		= rm -f
CFLAGS 	= -Wall -Werror -Wextra -fsanitize=address
NAME 	= philo
AR		= ar rc

all:		$(NAME)

$(NAME):	$(OBJS)	
			$(CC)  $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "\033[032mPHILO COMPILATION SUCCEEDED\033[0m"

clean:
			$(RM) $(OBJS)
			@echo "\033[38;5;208mOBJECTS DELETED\033[0m"

fclean:			clean
			$(RM) $(NAME)
			@echo "\033[031mPROGRAM DELETED\033[0m"

re:			fclean all

.PHONY:		all clean re fclean

.SILENT:

