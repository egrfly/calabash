/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_token_content.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:34:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 05:47:26 by emflynn          ###   ########.fr       */
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
		if (!ft_strncmp(&input[start_index],
				g_operator_symbols[i],
				chars_count))
		{
			return (i);
		}
	}
	return (0);
}
