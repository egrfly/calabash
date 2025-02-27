/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:30:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/27 20:58:29 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../debug/debug.h"
#include "../../execute/execute.h"
#include "../../lex/lex.h"
#include "../../lex/tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../../parse/parse.h"
#include "../../parse/tree_lifecycle/tree_lifecycle.h"
#include "../interface.h"
#include "./token_processors.h"

#ifndef DEBUG_LEXING
# define DEBUG_LEXING 0
#endif
#ifndef DEBUG_PARSING
# define DEBUG_PARSING 0
#endif

static void	print_processing_error(
				char *program_name,
				char *description,
				t_token	*token)
{
	ft_dprintf(STDERR_FILENO,
		"%s: %s near line %d, char %d: %s\n",
		program_name,
		description,
		token->start_line_index + 1,
		token->start_index_in_start_line + 1,
		token->surrounding_context);
	ft_dprintf(STDERR_FILENO,
		"%*s%.*s\n",
		token->start_index_in_context
		+ ft_strlen(program_name)
		+ ft_strlen(": ")
		+ ft_strlen(description)
		+ ft_strlen(" near line ")
		+ ft_nbrlen(token->start_line_index + 1, 10)
		+ ft_strlen(", char ")
		+ ft_nbrlen(token->start_index_in_start_line + 1, 10)
		+ ft_strlen(": "),
		"",
		token->length_in_context,
		"^^^^^^^^^^");
}

static int	process_syntax_tree(
				t_tokens_with_status *tokens_with_status,
				t_syntax_tree *syntax_tree,
				char *program_name,
				char **envp)
{
	if (!syntax_tree)
		return (ft_dprintf(STDERR_FILENO,
				"%s: out of memory\n", program_name),
			GENERAL_FAILURE);
	if (syntax_tree->contains_unsupported_features)
		return (print_processing_error(program_name, "unsupported feature",
				get_first_unsupported_token(tokens_with_status->tokens)),
			INCORRECT_USAGE);
	if (syntax_tree->some_tokens_left_unconsumed)
		return (print_processing_error(program_name, "syntax error",
				get_first_unconsumed_token(tokens_with_status->tokens)),
			INCORRECT_USAGE);
	if (DEBUG_PARSING)
		return (print_syntax_tree(syntax_tree->tree), SUCCESS);
	return (execute(syntax_tree->tree, program_name, envp));
}

int	process_tokens(
		t_tokens_with_status *tokens_with_status,
		t_multiline_options *multiline_options,
		char *program_name,
		char **envp)
{
	t_syntax_tree	*syntax_tree;
	int				status;

	if (!tokens_with_status || tokens_with_status->out_of_memory)
		return (ft_dprintf(STDERR_FILENO,
				"%s: out of memory\n", program_name),
			GENERAL_FAILURE);
	if (tokens_with_status->contains_unsupported_features)
		return (print_processing_error(program_name, "unsupported feature",
				get_first_unsupported_token(tokens_with_status->tokens)),
			INCORRECT_USAGE);
	if (tokens_with_status->input_terminated_prematurely)
		return (ft_dprintf(STDERR_FILENO,
				"%s: an opening quote was not closed\n", program_name),
			INCORRECT_USAGE);
	if (DEBUG_LEXING)
		return (print_tokens(tokens_with_status->tokens), SUCCESS);
	syntax_tree = parse(tokens_with_status->tokens, multiline_options);
	status = process_syntax_tree(tokens_with_status, syntax_tree,
			program_name, envp);
	destroy_syntax_tree(syntax_tree);
	destroy_tokens_with_status(tokens_with_status);
	return (status);
}
