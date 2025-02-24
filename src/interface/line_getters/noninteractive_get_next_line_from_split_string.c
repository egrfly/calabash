/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_get_next_line_from_split_str        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:08:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/24 19:24:35 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./line_getters.h"

char	*access_input_lines(t_access_mode mode, char **new_input_lines)
{
	static char	**input_lines;
	static int	latest_input_line_index;
	char		*latest_input_line;

	if (mode == SET)
	{
		input_lines = new_input_lines;
		latest_input_line_index = 0;
		return (NULL);
	}
	if (mode == GET && input_lines)
	{
		latest_input_line = input_lines[latest_input_line_index++];
		if (!latest_input_line)
		{
			free(input_lines);
			input_lines = NULL;
			latest_input_line_index = 0;
		}
		return (latest_input_line);
	}
	return (NULL);
}

char	*noninteractive_get_next_line_from_split_string(void *arg)
{
	(void)arg;
	return (access_input_lines(GET, LATEST_LINE));
}
