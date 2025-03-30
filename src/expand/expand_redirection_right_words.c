/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection_right_words.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:11:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 00:12:07 by emflynn          ###   ########.fr       */
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
#include "../parse/parse.h"
#include "./expand.h"
#include "./expand_pathnames/expand_pathnames.h"
#include "./expand_tildes/expand_tildes.h"
#include "./expand_variables/expand_variables.h"
#include "./here_doc_utils/here_doc_utils.h"
#include "./remove_quoting/remove_quoting.h"
#include "./split_fields/split_fields.h"

static bool	expand_pathname(
				char **right_word,
				char *right_word_before_expansion)
{
	t_list	*expanded_pathnames;
	char	*right_word_after_partial_expansion;

	right_word_after_partial_expansion = *right_word;
	expanded_pathnames = get_expanded_pathnames(
			right_word_after_partial_expansion);
	if (!expanded_pathnames)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	if (expanded_pathnames->size != 1)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: ambiguous redirect\n",
				get_program_name(), right_word_before_expansion),
			ft_list_destroy(expanded_pathnames, free), false);
	*right_word = ft_strdup(expanded_pathnames->first->value);
	free(right_word_after_partial_expansion);
	ft_list_destroy(expanded_pathnames, free);
	if (!*right_word)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	return (true);
}

static bool	expand_redirection_right_word(
				t_redirection *redirection,
				char *original_right_word,
				t_program_vars *program_vars)
{
	if (redirection->operator == LESS_LESS
		|| redirection->operator == LESS_LESS_DASH)
	{
		if (!redirection->heredoc_delimiter_involved_quoting
			&& !expand_here_doc(redirection, program_vars))
			return (unlink(redirection->right_content.word), false);
	}
	else
	{
		if (!expand_tildes(&redirection->right_content.word, program_vars)
			|| !expand_variables(&redirection->right_content.word, program_vars,
				NOT_HEREDOC))
			return (false);
		if (count_split_fields(redirection->right_content.word) != 1)
			return (ft_dprintf(STDERR_FILENO, "%s: %s: ambiguous redirect\n",
					get_program_name(), original_right_word), false);
		if (!expand_pathname(&redirection->right_content.word,
				original_right_word))
			return (false);
		remove_quoting(redirection->right_content.word, NOT_HEREDOC);
	}
	return (true);
}

bool	expand_redirection_right_words(
			t_list *redirections,
			t_program_vars *program_vars)
{
	t_list_node		*redirection_node;
	t_redirection	*redirection;
	char			*original_right_word;

	if (!redirections)
		return (true);
	redirection_node = redirections->first;
	while (redirection_node)
	{
		redirection = redirection_node->value;
		original_right_word = ft_strdup(redirection->right_content.word);
		if (!original_right_word)
			return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
					get_program_name()), false);
		if (!expand_redirection_right_word(redirection, original_right_word,
				program_vars))
			return (free(original_right_word), false);
		free(original_right_word);
		redirection_node = redirection_node->next;
	}
	return (true);
}
