/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_quote_mode_based_on_current_char.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:36:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 18:32:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_string.h"
#include "../../lex/lex.h"

bool	update_quote_mode_based_on_current_char(
			char *c,
			t_quote_mode *quote_mode,
			t_quote_mode base_quote_mode)
{
	if (*quote_mode == UNQUOTED && *c == '\\')
		*quote_mode = ESCAPED;
	else if (*quote_mode == UNQUOTED && *c == '\'')
		*quote_mode = SINGLE_QUOTED;
	else if (*quote_mode == UNQUOTED && *c == '\"')
		*quote_mode = DOUBLE_QUOTED;
	else if (*quote_mode == DOUBLE_QUOTED && *c == '\\'
		&& *(c + 1) && ft_strchr("$`\"\\", *(c + 1)))
		*quote_mode = DOUBLE_QUOTED_AND_ESCAPED;
	else if (*quote_mode == ESCAPED)
		*quote_mode = UNQUOTED;
	else if (*quote_mode == SINGLE_QUOTED && *c == '\'')
		*quote_mode = UNQUOTED;
	else if (*quote_mode == DOUBLE_QUOTED && *c == '\"'
		&& base_quote_mode != DOUBLE_QUOTED)
		*quote_mode = UNQUOTED;
	else if (*quote_mode == DOUBLE_QUOTED_AND_ESCAPED)
		*quote_mode = DOUBLE_QUOTED;
	else
		return (false);
	return (true);
}
