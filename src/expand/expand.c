/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:06:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/26 18:25:48 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../interface/interface.h"
#include "../interface/program_property_utils/program_property_utils.h"
#include "../lex/lex.h"
#include "../parse/parse.h"
#include "./expand.h"
#include "./expand_tildes/expand_tildes.h"
#include "./expand_variables/expand_variables.h"
#include "./remove_quoting/remove_quoting.h"
#include "./split_fields/split_fields.h"

bool	expand_assignment(
			t_list_node *assignment_node,
			t_program_vars *program_vars)
{
	if (!expand_tildes((char **)&assignment_node->value, program_vars))
		return (false);
	if (!expand_variables((char **)&assignment_node->value, program_vars, NOT_HEREDOC))
		return (false);
	remove_quoting(assignment_node->value, NOT_HEREDOC);
	return (true);
}

bool	expand_assignments(
			t_list *assignments,
			t_program_vars *program_vars)
{
	t_list_node	*assignment_node;

	assignment_node = assignments->first;
	while (assignment_node)
	{
		if (!expand_assignment(assignment_node, program_vars))
			return (false);
		assignment_node = assignment_node->next;
	}
	return (true);
}

bool	expand_arguments(
			t_list **arguments,
			t_program_vars *program_vars)
{
	t_list		*original_arguments;
	t_list_node	*argument_node;
	t_list		*split_arguments;
	t_list		*split_fields_from_argument;

	original_arguments = *arguments;
	argument_node = original_arguments->first;
	while (argument_node)
	{
		if (!expand_tildes((char **)&argument_node->value, program_vars))
			return (false);
		if (!expand_variables((char **)&argument_node->value, program_vars, NOT_HEREDOC))
			return (false);
		argument_node = argument_node->next;
	}
	split_arguments = ft_list_init();
	if (!split_arguments)
		return (false);
	argument_node = original_arguments->first;
	while (argument_node)
	{
		split_fields_from_argument = get_split_fields(argument_node->value);
		if (!split_fields_from_argument)
		{
			ft_list_destroy(split_arguments, free);
			return (false);
		}
		ft_list_merge(split_arguments, split_fields_from_argument);
		argument_node = argument_node->next;
	}
	*arguments = split_arguments;
	ft_list_destroy(original_arguments, free);
	// pathname expansion - optional
	argument_node = split_arguments->first;
	while (argument_node)
	{
		remove_quoting(argument_node->value, NOT_HEREDOC);
		argument_node = argument_node->next;
	}
	return (true);
}

bool	expand_redirection_right_word(
			t_redirection *redirection,
			t_program_vars *program_vars)
{
	char	*original_right_word;

	original_right_word = ft_strdup(redirection->right_content.word);
	if (!original_right_word)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
					get_program_name()), false);
	if (redirection->operator == LESS_LESS
		|| redirection->operator == LESS_LESS_DASH)
	{
		if (remove_quoting(redirection->right_content.word, NOT_HEREDOC))
			redirection->heredoc_delimiter_involved_quoting = true;
	}
	else
	{
		if (!expand_tildes(&redirection->right_content.word, program_vars))
			return (free(original_right_word), false);
		if (!expand_variables(&redirection->right_content.word, program_vars, NOT_HEREDOC))
			return (free(original_right_word), false);
		if (count_split_fields(redirection->right_content.word) != 1)
			return (ft_dprintf(STDERR_FILENO, "%s: %s: ambiguous redirect\n",
					get_program_name(), original_right_word),
				free(original_right_word),  false);
		remove_quoting(redirection->right_content.word, NOT_HEREDOC);
	}
	return (free(original_right_word), true);
}

bool	expand_redirection_right_words(
			t_list *redirections,
			t_program_vars *program_vars)
{
	t_list_node	*redirection_node;

	redirection_node = redirections->first;
	while (redirection_node)
	{
		if (!expand_redirection_right_word(redirection_node->value, program_vars))
			return (false);
		redirection_node = redirection_node->next;
	}
	return (true);
}

// Open file, line-by-line: read line, write expanded version to new file getting more lines if needed. Finally, remove original file
// bool	expand_here_doc(
// 			t_redirection *redirection,
// 			t_program_vars *program_vars)
// {
// 	if (!redirection->heredoc_delimiter_involved_quoting)
// 	{
// 		// variable expansion
// 	}
// 	return (true);
// }
