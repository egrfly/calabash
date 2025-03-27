/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_quote_mode_based_on_current_char.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:36:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/27 16:43:16 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_string.h"
#include "../../lex/lex.h"

bool	update_quote_mode_based_on_current_char(
			char *c,
			bool is_heredoc,
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
	else if (*quote_mode == ESCAPED)
		*quote_mode = UNQUOTED;
	else if (*quote_mode == SINGLE_QUOTED && *c == '\'')
		*quote_mode = UNQUOTED;
	else if (*quote_mode == DOUBLE_QUOTED && *c == '\"' && !is_heredoc)
		*quote_mode = UNQUOTED;
	else if (*quote_mode == DOUBLE_QUOTED_AND_ESCAPED)
		*quote_mode = DOUBLE_QUOTED;
	else
		return (false);
	return (true);
}
