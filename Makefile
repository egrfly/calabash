# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 00:45:25 by emflynn           #+#    #+#              #
#    Updated: 2025/03/01 01:03:45 by emflynn          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=				calabash

MODE :=				.mode
BUILD_WITH_TIMESTAMP := .build
PREPARE :=			.prepare

SRC_DIR :=			./src
OBJ_DIR :=			./obj
LIB_DIR :=			./lib
TEST_DIR :=			./test

SRC_DIRS :=			$(shell find $(SRC_DIR) -type d)
OBJ_DIRS :=			$(SRC_DIRS:$(SRC_DIR)/%=$(OBJ_DIR)/%)

ALL_FILES :=		$(wildcard $(addsuffix /*,$(SRC_DIRS)))

SRCS :=				$(filter %.c,$(ALL_FILES))
OBJS :=				$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
MODE_DEPENDENT :=	interface/token_processors/process_tokens

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

define update_mode_if_different
	@if ! echo $(1) | cmp -s $(MODE) -; \
	then \
		echo $(1) > $(MODE); \
	else \
		echo "make[1]: \`.mode' is up to date."; \
	fi
endef

$(NAME):			turn-off-debugging

run:				$(NAME)
					./$(NAME)

test-lexing:		debug-lexing
					@cd $(TEST_DIR) && bash lexer_tests.sh

test-parsing:		debug-parsing
					@cd $(TEST_DIR) && bash parser_tests.sh

$(BUILD_WITH_TIMESTAMP):	\
					$(PREPARE) $(LIBFT) $(OBJS)
					$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)
					@touch $@

$(LIBFT):
					$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
					$(MKDIR) $(OBJ_DIRS)

$(OBJ_DIR)/$(MODE_DEPENDENT).o:	\
					$(SRC_DIR)/$(MODE_DEPENDENT).c $(MODE) | $(OBJ_DIR)
					$(CC) $(CFLAGS) -D $(shell cat $(MODE)) -c $< -o $@

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c | $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@

$(MODE):
					echo "NO_DEBUG" > $@

$(PREPARE):
					git config core.hooksPath .githooks
					@touch $@

all:				$(NAME)

bonus:				all

debug-lexing:		
					$(call update_mode_if_different,DEBUG_LEXING)
					@$(MAKE) $(BUILD_WITH_TIMESTAMP)

debug-parsing:		
					$(call update_mode_if_different,DEBUG_PARSING)
					@$(MAKE) $(BUILD_WITH_TIMESTAMP)

turn-off-debugging:
					$(call update_mode_if_different,NO_DEBUG)
					@$(MAKE) $(BUILD_WITH_TIMESTAMP)

clean:
					$(MAKE) -C $(LIBFT_DIR) fclean
					$(RM) -R $(OBJ_DIR)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				run \
					prepare \
					all \
					bonus \
					debug-lexing \
					test-lexing \
					debug-parsing \
					test-parsing \
					turn-off-debugging \
					clean \
					fclean \
					re
