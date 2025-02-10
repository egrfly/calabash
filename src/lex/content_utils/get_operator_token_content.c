/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_token_content.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:34:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 23:19:00 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static const char	*g_operator_symbols[] = {
	NULL,
	"||",
	"|&",
	"|",
	"&&",
	"&>>",
	"&>",
	"&",
	";;&",
	";;",
	";&",
	";",
	"<<<",
	"<<-",
	"<<",
	"<>",
	"<&",
	"<",
	">>",
	">|",
	">&",
	">",
	"((",
	"(",
	"))",
	")",
	NULL,
};

int	get_operator_token_content(
		char *input,
		int start_index,
		int chars_count)
{
	int	i;

	i = 1;
	while (g_operator_symbols[i])
	{
		if ((unsigned)chars_count <= ft_strlen(g_operator_symbols[i])
			&& ft_strstarts(&input[start_index],
				g_operator_symbols[i]))
			return (i);
		i++;
	}
	return (0);
}
