NAME		:= 2048
BUILD_DIR	:= .build
SRC_DIR		:= srcs
INCLUDE_DIR	:= includes
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3
CPPFLAGS	:= -MMD -MP -I $(INCLUDE_DIR)
SRCS		:= 		\
	main.c			\
	board.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)
RM			:= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ -lncurses

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re
