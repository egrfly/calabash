/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_symbol.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 03:52:08 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:48:37 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../lex/lex.h"

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

const char	*get_operator_symbol(t_operator operator)
{
	return (g_operator_symbols[operator]);
}
