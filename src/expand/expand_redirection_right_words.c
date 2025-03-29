/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection_right_words.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:11:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 21:50:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../main.h"
#include "../interface/interface.h"
#include "../interface/list_utils/list_utils.h"
#include "../interface/program_property_utils/program_property_utils.h"
#include "../parse/parse.h"
#include "./expand.h"
#include "./expand_tildes/expand_tildes.h"
#include "./expand_variables/expand_variables.h"
#include "./remove_quoting/remove_quoting.h"
#include "./split_fields/split_fields.h"

static t_list	*get_here_doc_lines(
					char *file_path)
{
	int		fd;
	t_list	*here_doc_lines;
	char	*here_doc_line;

	fd = open(file_path, O_RDONLY);
	if (fd == OPEN_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: here-document failure\n",
				get_program_name()), NULL);
	here_doc_lines = ft_list_init();
	if (!here_doc_lines)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), close(fd), NULL);
	here_doc_line = ft_getline(fd);
	while (here_doc_line)
	{
		if (!ft_list_append(here_doc_lines, here_doc_line))
			return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
					get_program_name()),
				ft_list_destroy(here_doc_lines, free), close(fd), NULL);
		here_doc_line = ft_getline(fd);
	}
	return (close(fd), here_doc_lines);
}

static char	*get_here_doc_content(
				t_list	*here_doc_line_list,
				t_program_vars *program_vars)
{
	char	**here_doc_lines;
	char	*here_doc_content;

	here_doc_lines = get_values_from_list(here_doc_line_list);
	if (!here_doc_lines)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), NULL);
	here_doc_content = ft_arrjoin(here_doc_lines, "\n");
	ft_list_destroy(here_doc_line_list, free);
	free(here_doc_lines);
	if (!here_doc_content)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), NULL);
	if (!expand_variables(&here_doc_content, program_vars, IS_HEREDOC))
		return (free(here_doc_content), NULL);
	remove_quoting(here_doc_content, IS_HEREDOC);
	return (here_doc_content);
}

static bool	expand_here_doc(
				t_redirection *redirection,
				t_program_vars *program_vars)
{
	int		fd;
	t_list	*here_doc_lines;
	char	*here_doc_content;

	here_doc_lines = get_here_doc_lines(redirection->right_content.word);
	if (!here_doc_lines)
		return (false);
	here_doc_content = get_here_doc_content(here_doc_lines, program_vars);
	if (!here_doc_content)
		return (false);
	fd = open(redirection->right_content.word, O_WRONLY | O_TRUNC);
	if (fd == OPEN_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: here-document failure\n",
				get_program_name()), free(here_doc_content), false);
	ft_dprintf(fd, "%s\n", here_doc_content);
	return (free(here_doc_content), close(fd), true);
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
