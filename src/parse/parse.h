/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:13:10 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 15:35:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>
# include "ft_binary_tree.h"
# include "ft_list.h"
# include "../interface/interface.h"
# include "../lex/lex.h"

# define UPDATE_NO_OP 0
# define DELETE_NO_OP 0

# define OPTIONAL true
# define MANDATORY false

# define SUPPORTED true
# define UNSUPPORTED false

# define SHOULD_PROMPT_MORE_IN_INTERACTIVE_MODE true
# define SHOULD_NOT_PROMPT_MORE_IN_INTERACTIVE_MODE false

typedef enum e_syntax_tree_node_value_type
{
	SIMPLE_COMMAND,
	GROUP,
	SUBSHELL,
	WHILE_COMMAND,
	UNTIL_COMMAND,
	IF_COMMAND,
	FOR_COMMAND,
	SELECT_COMMAND,
	CASE_COMMAND,
	FUNCTION,
	PIPE,
	PIPE_BOTH,
	TIME_COMMAND,
	NEGATION,
	OR,
	AND,
	SEQUENCE,
	BACKGROUND,
	COPROCESS,
}	t_syntax_tree_node_value_type;

typedef enum e_redirection_left_type
{
	NO_REDIRECTION_LEFT_CONTENT,
	REDIRECTION_LEFT_NUMBER,
	REDIRECTION_LEFT_REDIRECTION_WORD,
}	t_redirection_left_type;

typedef enum e_redirection_right_type
{
	NO_REDIRECTION_RIGHT_CONTENT,
	REDIRECTION_RIGHT_DASH,
	REDIRECTION_RIGHT_NUMBER_DASH,
	REDIRECTION_RIGHT_NUMBER,
	REDIRECTION_RIGHT_WORD,
}	t_redirection_right_type;

typedef union u_redirection_left_content
{
	int		number;
	char	*redirection_word;
}	t_redirection_left_content;

typedef union u_redirection_right_content
{
	int		number;
	char	*word;
}	t_redirection_right_content;

typedef struct s_redirection_reset_instruction
{
	bool	is_active;
	int		original_fd;
	int		fd_to_reset;
}	t_redirection_reset_instruction;

typedef struct s_redirection
{
	t_redirection_left_type			left_type;
	t_redirection_left_content		left_content;
	t_operator						operator;
	t_redirection_right_type		right_type;
	t_redirection_right_content		right_content;
	bool							heredoc_delimiter_involved_quoting;
	t_redirection_reset_instruction	primary_reset_instruction;
	t_redirection_reset_instruction	secondary_reset_instruction;
}	t_redirection;

typedef struct s_syntax_tree_node_value
{
	t_syntax_tree_node_value_type	type;
	t_list							*assignments;
	t_list							*arguments;
	t_list							*redirections;
	bool							is_terminated;
	bool							time_posix_option_set;
	char							*coprocess_custom_identifier;
	char							*function_identifier;
}	t_syntax_tree_node_value;

typedef struct s_syntax_tree
{
	t_binary_tree		*tree;
	t_binary_tree_node	*current_node;
	t_list				*undo_actions;
	bool				out_of_memory;
	bool				contains_unsupported_features;
	bool				some_tokens_left_unconsumed;
	bool				quoted_section_not_closed;
	bool				expanded_section_not_closed;
	bool				here_doc_failure;
}	t_syntax_tree;

typedef int		(*t_token_consumption_func)(
	void *arg,
	t_list_node **current_token_node,
	t_syntax_tree *syntax_tree,
	t_multiline_options *multiline_options);

typedef bool	(*t_tree_update_func)(
	t_syntax_tree *syntax_tree,
	t_list_node *current_token_node,
	t_multiline_options *multiline_options);

typedef void	(*t_tree_undo_action_func)(
	t_syntax_tree *syntax_tree);

typedef struct s_parsing_option
{
	t_token_consumption_func	token_consumption_func;
	void						*token_consumption_func_arg;
	t_tree_update_func			tree_update_func;
	bool						is_optional;
	bool						is_supported;
}	t_parsing_option;

typedef struct s_parsing_option_sequence_with_count
{
	char					*name;
	const t_parsing_option	*sequence;
	int						count;
}	t_parsing_option_sequence_with_count;

t_syntax_tree	*parse(
					t_list *tokens,
					t_multiline_options *multiline_options);

#endif
