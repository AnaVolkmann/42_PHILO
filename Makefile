SRCS 	= main.c utils.c handle_args.c init.c monitor.c routine_actions.c threads.c
OBJS 	= $(SRCS:.c=.o)
CC	 	= cc
RM 		= rm -f
CFLAGS 	= -g -Wall -Werror -Wextra -fsanitize=thread
NAME 	= philo

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

