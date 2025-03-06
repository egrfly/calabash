/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_token_content.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:34:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 03:51:21 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "../lex.h"

static const
	char
	*g_operator_symbols[] = {
[BAR_BAR] = "||",
[BAR_AMPERSAND] = "|&",
[BAR] = "|",
[AMPERSAND_AMPERSAND] = "&&",
[AMPERSAND_GREATER_GREATER] = "&>>",
[AMPERSAND_GREATER] = "&>",
[AMPERSAND] = "&",
[SEMICOLON_SEMICOLON_AMPERSAND] = ";;&",
[SEMICOLON_SEMICOLON] = ";;",
[SEMICOLON_AMPERSAND] = ";&",
[SEMICOLON] = ";",
[LESS_LESS_LESS] = "<<<",
[LESS_LESS_DASH] = "<<-",
[LESS_LESS] = "<<",
[LESS_GREATER] = "<>",
[LESS_AMPERSAND] = "<&",
[LESS] = "<",
[GREATER_GREATER] = ">>",
[GREATER_BAR] = ">|",
[GREATER_AMPERSAND] = ">&",
[GREATER] = ">",
[OPENING_PARENTHESIS_PARENTHESIS] = "((",
[OPENING_PARENTHESIS] = "(",
[CLOSING_PARENTHESIS_PARENTHESIS] = "))",
[CLOSING_PARENTHESIS] = ")",
};

t_operator	get_operator_token_content(
		char *input,
		int start_index,
		int chars_count)
{
	size_t	i;

	i = 1;
	while (i < sizeof(g_operator_symbols) / sizeof(char *))
	{
		if ((unsigned)chars_count <= ft_strlen(g_operator_symbols[i])
			&& ft_strstarts(&input[start_index],
				g_operator_symbols[i]))
			return (i);
		i++;
	}
	return (NO_OPERATOR);
}
