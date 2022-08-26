NAME		=	ft_shmup

CC			=	c++

CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -Iinclude -lncurses
ifeq ($(DEBUG), 1)
	CFLAGS		+= -DDEBUG=1
endif

SRCS		=	$(wildcard srcs/*.cpp)

OBJS		=	$(SRCS:.cpp=.o)
DEPS		=	$(OBJS:.o=.d)

%.o : %.cpp
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS) $(DEPS)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean
				$(MAKE)

debug		:	fclean
				$(MAKE) DEBUG=1

-include $(DEPS)

.PHONY: all clean fclean re -include debug