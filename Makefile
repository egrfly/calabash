# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 00:45:25 by emflynn           #+#    #+#              #
#    Updated: 2025/02/27 22:05:09 by emflynn          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=				calabash

EXEC_MODE_FILE :=	./.execmode
BUILD_WITH_TIMESTAMP :=	./.build

SRC_DIR :=			./src
OBJ_DIR :=			./obj
LIB_DIR :=			./lib
TEST_DIR :=			./test

SRC_DIRS :=			$(shell find $(SRC_DIR) -type d)
OBJ_DIRS :=			$(SRC_DIRS:$(SRC_DIR)/%=$(OBJ_DIR)/%)

ALL_FILES :=		$(wildcard $(addsuffix /*,$(SRC_DIRS)))

SRCS :=				$(filter %.c,$(ALL_FILES))
OBJS :=				$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC_MODE_DEPENDENT :=	interface/token_processors/process_tokens

LIBFT_DIR :=		$(LIB_DIR)/libft
LIBFT :=			$(LIBFT_DIR)/libft.a
LIBFT_LIB := 		$(LIBFT_DIR)
LIBFT_INCLUDE :=	$(LIBFT_DIR)/include

CC :=				cc
CFLAGS :=			-Wall -Wextra -Werror -I $(LIBFT_INCLUDE)
LDFLAGS :=			-L $(LIBFT_LIB)
LDLIBS :=			-lreadline -lft
MAKE :=				make
MKDIR :=			mkdir -p
RM :=				rm -f

define update_execmode_if_different
	@if ! cmp --silent $(EXEC_MODE_FILE) - <<< "$(1)"; \
	then \
		echo $(1) > $(EXEC_MODE_FILE); \
	else \
		echo "make: \`.execmode' unchanged."; \
	fi
endef

$(NAME):			turn-off-debugging $(BUILD_WITH_TIMESTAMP)

test-lexing:		debug-lexing $(BUILD_WITH_TIMESTAMP)
					@cd $(TEST_DIR) && bash lexer_tests.sh

test-parsing:		debug-parsing $(BUILD_WITH_TIMESTAMP)
					@cd $(TEST_DIR) && bash parser_tests.sh

$(BUILD_WITH_TIMESTAMP):	$(LIBFT) $(OBJS)
					$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)
					@touch $(BUILD_WITH_TIMESTAMP)

$(LIBFT):
					$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
					$(MKDIR) $(OBJ_DIRS)

$(OBJ_DIR)/$(EXEC_MODE_DEPENDENT).o:	\
					$(SRC_DIR)/$(EXEC_MODE_DEPENDENT).c $(EXEC_MODE_FILE) | $(OBJ_DIR)
					$(CC) $(CFLAGS) -D $(shell cat $(EXEC_MODE_FILE)) -c $< -o $@

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c | $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@

$(EXEC_MODE_FILE):
					echo "NO_DEBUG" > $@

all:				$(NAME)

bonus:				all

debug-lexing:		
					$(call update_execmode_if_different,DEBUG_LEXING)

debug-parsing:		
					$(call update_execmode_if_different,DEBUG_PARSING)

turn-off-debugging:
					$(call update_execmode_if_different,NO_DEBUG)

clean:
					$(MAKE) -C $(LIBFT_DIR) fclean
					$(RM) -R $(OBJ_DIR)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all \
					bonus \
					debug-lexing \
					test-lexing \
					debug-parsing \
					test-parsing \
					turn-off-debugging \
					clean \
					fclean \
					re
