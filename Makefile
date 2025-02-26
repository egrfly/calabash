# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 00:45:25 by emflynn           #+#    #+#              #
#    Updated: 2025/02/26 16:20:23 by emflynn          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=				calabash

SRC_DIR :=			./src
OBJ_DIR :=			./obj
LIB_DIR :=			./lib

SRC_DIRS :=			$(shell find $(SRC_DIR) -type d)
OBJ_DIRS :=			$(SRC_DIRS:$(SRC_DIR)/%=$(OBJ_DIR)/%)

ALL_FILES :=		$(wildcard $(addsuffix /*,$(SRC_DIRS)))

SRCS :=				$(filter %.c,$(ALL_FILES))
OBJS :=				$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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

$(NAME):			$(LIBFT) $(OBJS)
					$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(LIBFT):
					$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
					$(MKDIR) $(OBJ_DIRS)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c | $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

bonus:				all

clean:
					$(MAKE) -C $(LIBFT_DIR) fclean
					$(RM) -R $(OBJ_DIR)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all bonus clean fclean re
