/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:21:28 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 21:55:16 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# define DEFAULT_START_LINE_INDEX 0

# define BLANK_TOKEN_LENGTH_IN_CONTEXT 3
# define MAX_TOKEN_LENGTH_IN_CONTEXT 10
# define MAX_LEADING_CONTEXT_LENGTH 5
# define MAX_TRAILING_CONTEXT_LENGTH 5
# define ELLIPSIS_LENGTH 3

# include <stdbool.h>
# include <stdlib.h>
# include "ft_list.h"

typedef enum e_quote_mode
{
	UNQUOTED,
	ESCAPED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	DOUBLE_QUOTED_AND_ESCAPED,
	MAX_QUOTE_MODE,
}	t_quote_mode;

typedef enum e_nesting_mode
{
	NOT_NESTED,
	DOLLAR_PARENTHESIS_PARENTHESIS,
	DOLLAR_PARENTHESIS,
	DOLLAR_BRACE,
	LESS_PARENTHESIS,
	GREATER_PARENTHESIS,
	PARENTHESIS_PARENTHESIS,
	PARENTHESIS,
	BACKTICK,
	MAX_NESTING_MODE,
}	t_nesting_mode;

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
	OPERATOR_COUNT,
}	t_operator;

typedef enum e_token_type
{
	WORD,
	OPERATOR,
	NEWLINE,
	WHITESPACE,
	END_OF_INPUT,
}	t_token_type;

typedef union u_token_content
{
	char		*word;
	t_operator	operator;
}	t_token_content;

typedef struct s_multiline_options
{
	bool	input_mode_is_interactive;
	char	*(*get_next_line)(void *arg);
	void	*get_next_line_arg;
}	t_multiline_options;

typedef struct s_input_tracker
{
	char			*input;
	int				line_index;
	int				index_in_line;
	t_quote_mode	quote_mode;
	t_nesting_mode	nesting_mode;
	bool			is_out_of_lines;
}	t_input_tracker;

typedef struct s_token
{
	t_token_type	type;
	int				start_line_index;
	int				start_index_in_start_line;
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
	bool	terminated_prematurely;
}	t_tokens_with_status;

t_tokens_with_status	*lex(char *input,
							t_multiline_options *multiline_options,
							int start_line_index);

#endif
