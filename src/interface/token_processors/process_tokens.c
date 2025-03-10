/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:30:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 23:03:45 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../debug/debug.h"
#include "../../execute/execute.h"
#include "../../execute/signals/signals.h"
#include "../../lex/lex.h"
#include "../../lex/token_lifecycle/token_lifecycle.h"
#include "../../lex/token_utils/token_utils.h"
#include "../../parse/parse.h"
#include "../../parse/tree_lifecycle/tree_lifecycle.h"
#include "../interface.h"
#include "../file_utils/file_utils.h"
#include "../line_getters/line_getters.h"
#include "../program_name_utils/program_name_utils.h"
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

static int	handle_parsing_error(
				t_syntax_tree *syntax_tree,
				t_list *tokens,
				char *program_name)
{
	if (!syntax_tree || syntax_tree->out_of_memory)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				program_name), GENERAL_FAILURE);
	if (syntax_tree->here_doc_failure)
		return (GENERAL_FAILURE);
	if (syntax_tree->contains_unsupported_features)
		return (print_processing_error(program_name,
				"unsupported feature", get_first_unsupported_token(
					tokens)), GENERAL_FAILURE);
	if (syntax_tree->input_terminated_prematurely && g_signal != SIGINT)
		return (print_processing_error(program_name,
				"unclosed quote",
				get_penultimate_token_with_context_focused_on_quote(
					tokens)), INCORRECT_USAGE);
	if (syntax_tree->some_tokens_left_unconsumed && g_signal != SIGINT)
		return (print_processing_error(program_name,
				"syntax error", get_first_unconsumed_token(
					tokens)), INCORRECT_USAGE);
	return (SUCCESS);
}

static int	process_syntax_tree(
				t_list *tokens,
				t_syntax_tree *syntax_tree,
				t_program_vars *program_vars)
{
	int							parsing_status;
	t_tokens_and_syntax_tree	tokens_and_syntax_tree;

	parsing_status = handle_parsing_error(syntax_tree, tokens,
			get_program_name());
	if (parsing_status != SUCCESS)
		return (parsing_status);
	if (DEBUG_PARSING)
		return (print_syntax_tree(syntax_tree->tree), SUCCESS);
	ft_bzero(&tokens_and_syntax_tree, sizeof(tokens_and_syntax_tree));
	tokens_and_syntax_tree.tokens = tokens;
	tokens_and_syntax_tree.syntax_tree = syntax_tree;
	return (execute(&tokens_and_syntax_tree, program_vars));
}

static int	handle_lexing_error(
				t_tokens_with_status *tokens_with_status,
				char *program_name)
{
	if (!tokens_with_status || tokens_with_status->out_of_memory)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				program_name), GENERAL_FAILURE);
	if (tokens_with_status->contains_unsupported_features)
		return (print_processing_error(program_name,
				"unsupported feature", get_first_unsupported_token(
					tokens_with_status->tokens)), GENERAL_FAILURE);
	if (tokens_with_status->input_terminated_prematurely)
		return (print_processing_error(program_name,
				"unclosed quote",
				get_penultimate_token_with_context_focused_on_quote(
					tokens_with_status->tokens)), INCORRECT_USAGE);
	return (SUCCESS);
}

int	process_tokens(
		t_tokens_with_status *tokens_with_status,
		t_multiline_options *multiline_options,
		t_program_vars *program_vars)
{
	int				input_fd;
	int				lexing_status;
	t_list			*tokens;
	t_syntax_tree	*syntax_tree;
	int				exit_status;

	if (multiline_options->get_next_line
		== noninteractive_get_next_line_from_file_descriptor)
		input_fd = *(int *)multiline_options->get_next_line_arg;
	else
		input_fd = -1;
	lexing_status = handle_lexing_error(tokens_with_status, get_program_name());
	if (lexing_status != SUCCESS)
		return (close_if_opened(input_fd), lexing_status);
	tokens = tokens_with_status->tokens;
	free(tokens_with_status);
	if (DEBUG_LEXING)
		return (close_if_opened(input_fd), print_tokens(tokens), SUCCESS);
	syntax_tree = parse(tokens, multiline_options);
	close_if_opened(input_fd);
	exit_status = process_syntax_tree(tokens, syntax_tree, program_vars);
	destroy_syntax_tree(syntax_tree);
	ft_list_destroy(tokens, (t_action_func)destroy_token);
	return (exit_status);
}
