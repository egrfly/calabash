/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 23:42:29 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 23:44:23 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/list_utils/list_utils.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../parse/parse.h"
#include "../expand.h"
#include "../expand_variables/expand_variables.h"
#include "../remove_quoting/remove_quoting.h"

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
	if (here_doc_line_list->first)
		here_doc_content = ft_arrjoin(here_doc_lines, "\n");
	else
		here_doc_content = ft_strdup("");
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

bool	expand_here_doc(
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
