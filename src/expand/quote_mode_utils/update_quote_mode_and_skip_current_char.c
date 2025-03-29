/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_quote_mode_if_skippable_based_on_cur        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:14:00 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 19:31:54 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_string.h"
#include "../../lex/lex.h"

bool	update_quote_mode_and_skip_current_char(
			char *c,
			t_quote_mode *quote_mode)
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
	else if (*quote_mode == SINGLE_QUOTED && *c == '\'')
		*quote_mode = UNQUOTED;
	else if (*quote_mode == DOUBLE_QUOTED && *c == '\"')
		*quote_mode = UNQUOTED;
	else
		return (false);
	return (true);
}
