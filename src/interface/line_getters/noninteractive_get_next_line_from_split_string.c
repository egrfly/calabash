/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_get_next_line_from_split_str        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:08:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/01 02:03:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./line_getters.h"

static void	reset_input_lines(
				char ***input_lines,
				int *latest_input_line_index)
{
	free(*input_lines);
	*input_lines = NULL;
	*latest_input_line_index = 0;
}

char	*access_input_lines(
			t_access_mode mode,
			char **new_input_lines)
{
	static char	**input_lines;
	static int	latest_input_line_index;
	char		*latest_input_line;

	if (mode == SET)
		input_lines = new_input_lines;
	else if (mode == GET && input_lines)
	{
		latest_input_line = input_lines[latest_input_line_index++];
		if (!latest_input_line)
			reset_input_lines(&input_lines, &latest_input_line_index);
		return (latest_input_line);
	}
	else if (mode == DELETE && input_lines)
	{
		latest_input_line = input_lines[latest_input_line_index++];
		while (latest_input_line)
		{
			free(latest_input_line);
			latest_input_line = input_lines[latest_input_line_index++];
		}
		reset_input_lines(&input_lines, &latest_input_line_index);
	}
	return (NULL);
}

char	*noninteractive_get_next_line_from_split_string(
			void *arg)
{
	(void)arg;
	return (access_input_lines(GET, LATEST_LINE));
}
