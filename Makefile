NAME			:= 2048
BUILD_DIR		:= .build
SRC_DIR			:= srcs
INCLUDE_DIR		:= includes
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3
CPPFLAGS		:= -MMD -MP -I $(INCLUDE_DIR) 

SRCS			:= 		\
	main.c				\
	board.c				\
	logic_game.c		\
	fill_grid_numbers.c \
	display.c			\
	check_game_over.c	\
	game_logic_utils.c	\
	font.c				\
	utils.c

SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS			:= $(OBJS:.o=.d)
RM				:= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lncurses

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

force:

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME)

debug:
	$(MAKE) re CFLAGS="-Wall -Wextra -g3 -D DEBUG=1"

-include $(DEPS)

.PHONY: all clean fclean re run debug
