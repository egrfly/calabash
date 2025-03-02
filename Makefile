# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 00:45:25 by emflynn           #+#    #+#              #
#    Updated: 2025/03/02 23:16:24 by emflynn          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=				calabash

MODE :=				.mode
PREPARE :=			.prepare
BUILD_WITH_TIMESTAMP := .build

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
MAKEFLAGS :=		--no-print-directory
MKDIR :=			mkdir -p
RM :=				rm -f

define update_mode_and_rebuild_if_necessary
	CYAN='\033[36m'; \
	GREEN='\033[32m'; \
	RED='\033[31m'; \
	END='\033[0m'; \
	CLEAR='\033[K'; \
	CHAR='|'; \
	advance_char() { \
		if [ $${CHAR} = '|' ]; then CHAR='/'; sleep 0.15; \
		elif [ $${CHAR} = '/' ]; then CHAR='-'; sleep 0.18; \
		elif [ $${CHAR} = '-' ]; then CHAR='\'; sleep 0.15; \
		elif [ $${CHAR} = '\' ]; then CHAR='|'; sleep 0.12; \
		fi; \
	}; \
	update_mode() { \
		if echo $(1) | cmp -s $(MODE) -; then return 1; \
		elif echo $(1) > $(MODE); then return 0; \
		else return 2; \
		fi; \
	}; \
	update_using_make() { \
		TEMP=$$(mktemp); \
		if ! $(MAKE) $(MAKEFLAGS) $${1} > $${TEMP}; then RETURN_VALUE=2; \
		elif cat $${TEMP} | grep -q "up to date"; then RETURN_VALUE=1; \
		else RETURN_VALUE=0; \
		fi; \
		$(RM) $${TEMP}; \
		return $${RETURN_VALUE}; \
	}; \
	update_submodules() { \
		update_using_make $(PREPARE); \
	}; \
	update_libft() { \
		update_using_make $(LIBFT); \
	}; \
	update_calabash() { \
		update_using_make $(BUILD_WITH_TIMESTAMP); \
	}; \
	display_waiting_message() { \
		while kill -0 $${!} 2> /dev/null; \
		do printf "[$${CYAN}$${1}$${END}] $${2} $${CHAR} \r"; advance_char; \
		done; \
	}; \
	perform_update_if_necessary() { \
		{ \
			$$($${1} 2> /dev/null); \
			RETURN_VALUE=$${?}; \
			if [ $${RETURN_VALUE} -eq 0 ]; then \
				echo "$${CLEAR}[$${GREEN}$${2}$${END}] $${4}."; \
			elif [ $${RETURN_VALUE} -eq 1 ]; then \
				echo "$${CLEAR}[$${GREEN}$${2}$${END}] $${5}."; \
			else \
				echo "$${CLEAR}[$${RED}$${2}$${END}] $${6}."; \
			fi; \
		} & \
		display_waiting_message "$${2}" "$${3}"; \
	}; \
	perform_update_if_necessary update_mode "MODES" \
		"Selecting mode $(1)" "Mode now set to $(1)" \
		"Mode already set to $(1)" "Error setting mode"; \
	perform_update_if_necessary update_submodules "CLONE" \
		"Preparing submodules" "Submodules ready" \
		"Submodules already cloned" "Error cloning submodules"; \
	perform_update_if_necessary update_libft "LIBFT" \
		"Preparing Libft" "Libft ready" \
		"Libft already up to date" "Error preparing libft"; \
	perform_update_if_necessary update_calabash "BUILD" \
		"Preparing Calabash" "Calabash ready" \
		"Calabash already up to date" "Error preparing calabash"
endef

$(NAME):			turn-off-debugging

run:				$(NAME)
					@./$(NAME)

test-lexing:		debug-lexing
					@cd $(TEST_DIR) && bash lexer_tests.sh

test-parsing:		debug-parsing
					@cd $(TEST_DIR) && bash parser_tests.sh

$(OBJ_DIR):
					@$(MKDIR) $(OBJ_DIRS)

$(OBJ_DIR)/$(MODE_DEPENDENT).o:	\
					$(SRC_DIR)/$(MODE_DEPENDENT).c $(MODE) | $(OBJ_DIR)
					@$(CC) $(CFLAGS) -D $(shell cat $(MODE)) -c $< -o $@

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c | $(OBJ_DIR)
					@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
					@$(MAKE) $(MAKEFLAGS) -C $(LIBFT_DIR)

$(MODE):
					@echo "NO_DEBUG" > $@

$(PREPARE):
					@git config core.hooksPath .githooks
					@git submodule update --quiet --init --recursive
					@touch $@

$(BUILD_WITH_TIMESTAMP):	\
					$(OBJS)
					@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)
					@touch $@

all:				$(NAME)

bonus:				all

debug-lexing:
					@$(call update_mode_and_rebuild_if_necessary,DEBUG_LEXING)

debug-parsing:
					@$(call update_mode_and_rebuild_if_necessary,DEBUG_PARSING)

turn-off-debugging:
					@$(call update_mode_and_rebuild_if_necessary,NO_DEBUG)

clean:
					@git submodule foreach -q \
						"if [ -f Makefile ]; then \
							$(MAKE) $(MAKEFLAGS) fclean; \
						fi"
					@$(RM) -R $(OBJ_DIR)

fclean:				clean
					@$(RM) $(NAME)

re:					fclean all

.PHONY:				run \
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
