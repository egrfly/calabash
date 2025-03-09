/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_redirection_if_here_doc_or_string.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:47:25 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 02:36:51 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../temp_file_utils/temp_file_utils.h"
#include "../../execute/signals/signals.h"

#define SHOULD_STRIP_LEADING_TABS true
#define SHOULD_NOT_STRIP_LEADING_TABS false

static char	*adjust_line_start_if_necessary(
				char *line,
				bool should_strip_leading_tabs)
{
	if (should_strip_leading_tabs)
		return (&line[ft_strspn(line, "\t")]);
	else
		return (line);
}

static bool	add_here_doc_content_to_temp_file(
				char *temp_file_path,
				char *delimiter,
				bool should_strip_leading_tabs)
{
	int		fd;
	char	*line;

	fd = open(temp_file_path, O_WRONLY | O_TRUNC);
	if (fd == OPEN_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: here-document failure\n",
				get_program_name()), false);
	line = readline("> ");
	while (g_signal != SIGINT && line
		&& ft_strcmp(adjust_line_start_if_necessary(line,
				should_strip_leading_tabs), delimiter))
	{
		if (ft_dprintf(fd, "%s\n", adjust_line_start_if_necessary(line,
					should_strip_leading_tabs)) == WRITE_FAILURE)
			return (free(line), close(fd), ft_dprintf(STDERR_FILENO,
					"%s: here-document failure\n", get_program_name()), false);
		free(line);
		line = readline("> ");
		if (g_signal == SIGINT)
			return (close(fd), free(line), line = NULL, false);
	}
	if (!line)
		ft_dprintf(STDERR_FILENO, "%s: warning: here-document delimited "
			"by end-of-file (wanted `%s')\n", get_program_name(), delimiter);
	return (free(line), close(fd), true);
}

static bool	add_here_string_content_to_temp_file(
				char *temp_file_path,
				char *content)
{
	int		fd;

	fd = open(temp_file_path, O_WRONLY | O_TRUNC);
	if (fd == OPEN_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: here-string failure\n",
				get_program_name()), false);
	if (ft_dprintf(fd, "%s\n", content) == WRITE_FAILURE)
	{
		close(fd);
		return (ft_dprintf(STDERR_FILENO, "%s: here-string failure\n",
				get_program_name()), false);
	}
	return (close(fd), true);
}

static bool	add_here_doc_or_string_content_to_temp_file(
				t_redirection *redirection,
				char *temp_file_path)
{
	return ((redirection->operator == LESS_LESS_LESS
			&& add_here_string_content_to_temp_file(temp_file_path,
				redirection->right_content.word))
		|| (redirection->operator == LESS_LESS_DASH
			&& add_here_doc_content_to_temp_file(temp_file_path,
				redirection->right_content.word,
				SHOULD_STRIP_LEADING_TABS))
		|| (redirection->operator == LESS_LESS
			&& add_here_doc_content_to_temp_file(temp_file_path,
				redirection->right_content.word,
				SHOULD_NOT_STRIP_LEADING_TABS)));
}

bool	update_redirection_if_here_doc_or_string(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node)
{
	t_syntax_tree_node_value	*current_node_value;
	t_redirection				*last_redirection;
	char						temp_file_path[PATH_MAX + 1];

	current_node_value = syntax_tree->current_node->value;
	last_redirection = current_node_value->redirections->last->value;
	if (last_redirection->operator == LESS_LESS_LESS
		|| last_redirection->operator == LESS_LESS_DASH
		|| last_redirection->operator == LESS_LESS)
	{
		make_temp_file(temp_file_path, syntax_tree, current_token_node->parent);
		if (g_signal == SIGINT
			|| !add_here_doc_or_string_content_to_temp_file(last_redirection,
				temp_file_path))
		{
			syntax_tree->here_doc_failure = true;
			return (unlink(temp_file_path), false);
		}
		free(last_redirection->right_content.word);
		last_redirection->right_content.word = ft_strdup(temp_file_path);
		if (!last_redirection->right_content.word)
			return (unlink(temp_file_path), false);
	}
	return (true);
}
