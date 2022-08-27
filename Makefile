NAME		=	ft_shmup

CC			=	c++
LIBS		=	-lncurses
CFLAGS		=	-Wall -Wextra -Werror -g3 -std=c++11 -I/usr/include/ -Iinclude
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
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

clean		:
				rm -rf $(OBJS) $(DEPS)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean
				$(MAKE) -j

debug		:	fclean
				$(MAKE) -j DEBUG=1

-include $(DEPS)

.PHONY: all clean fclean re -include debug
