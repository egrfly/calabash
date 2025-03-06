/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:21:28 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/04 04:51:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# define DEFAULT_LINE_INDEX 0

# define BLANK_TOKEN_LENGTH_IN_CONTEXT 3
# define MAX_TOKEN_LENGTH_IN_CONTEXT 10
# define MAX_LEADING_CONTEXT_LENGTH 5
# define MAX_TRAILING_CONTEXT_LENGTH 5
# define ELLIPSIS_LENGTH 3

# include <stdbool.h>
# include <stdlib.h>
# include "ft_list.h"
# include "../interface/interface.h"

typedef enum e_quote_mode
{
	UNQUOTED,
	ESCAPED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	DOUBLE_QUOTED_AND_ESCAPED,
}	t_quote_mode;

typedef enum e_expansion_mode
{
	NOT_EXPANDED_OR_SUBSTITUTED,
	ARITHMETIC_EXPANSION,
	COMMAND_SUBSTITUTION_WITH_DOLLAR_PARENTHESES,
	VARIABLE_EXPANSION_WITH_BRACES,
	VARIABLE_EXPANSION_WITHOUT_BRACES,
	PROCESS_SUBSTITUTION_WITH_LESS,
	PROCESS_SUBSTITUTION_WITH_GREATER,
	COMMAND_SUBSTITUTION_WITH_BACKTICKS,
}	t_expansion_mode;

typedef enum e_operator
{
	NO_OPERATOR,
	BAR_BAR,
	BAR_AMPERSAND,
	BAR,
	AMPERSAND_AMPERSAND,
	AMPERSAND_GREATER_GREATER,
	AMPERSAND_GREATER,
	AMPERSAND,
	SEMICOLON_SEMICOLON_AMPERSAND,
	SEMICOLON_SEMICOLON,
	SEMICOLON_AMPERSAND,
	SEMICOLON,
	LESS_LESS_LESS,
	LESS_LESS_DASH,
	LESS_LESS,
	LESS_GREATER,
	LESS_AMPERSAND,
	LESS,
	GREATER_GREATER,
	GREATER_BAR,
	GREATER_AMPERSAND,
	GREATER,
	OPENING_PARENTHESIS_PARENTHESIS,
	OPENING_PARENTHESIS,
	CLOSING_PARENTHESIS_PARENTHESIS,
	CLOSING_PARENTHESIS,
}	t_operator;

typedef enum e_token_type
{
	TYPE_WORD,
	TYPE_OPERATOR,
	TYPE_NEWLINE,
	TYPE_WHITESPACE,
	TYPE_END_OF_INPUT,
}	t_token_type;

typedef union u_token_content
{
	char		*word;
	t_operator	operator;
}	t_token_content;

typedef struct s_token
{
	t_token_type	type;
	int				start_line_index;
	int				start_index_in_start_line;
	int				last_opening_quote_line_start_index_in_word_content;
	int				last_opening_quote_index_in_word_content_line;
	int				last_opening_quote_line_index;
	int				last_opening_quote_index_in_line;
	int				end_line_index;
	t_token_content	content;
	char			surrounding_context[ELLIPSIS_LENGTH
		+ MAX_LEADING_CONTEXT_LENGTH
		+ MAX_TOKEN_LENGTH_IN_CONTEXT
		+ MAX_TRAILING_CONTEXT_LENGTH
		+ ELLIPSIS_LENGTH
		+ 1];
	int				start_index_in_context;
	int				length_in_context;
	bool			context_was_truncated;
	bool			is_delimited;
	bool			is_supported;
	bool			has_been_consumed_at_some_point;
}	t_token;

typedef struct s_tokens_with_status
{
	t_list	*tokens;
	bool	out_of_memory;
	bool	contains_unsupported_features;
	bool	input_terminated_prematurely;
}	t_tokens_with_status;

t_tokens_with_status	*lex(char *input,
							t_multiline_options *multiline_options,
							int start_line_index);

typedef struct s_input_tracker
{
	char			*input;
	int				line_index;
	int				index_in_line;
	t_quote_mode	quote_mode;
	bool			is_out_of_lines;
}	t_input_tracker;

#endif
