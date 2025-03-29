/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_quote_mode_if_not_skippable_based_on        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:16:08 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 19:32:00 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../lex/lex.h"

bool	update_quote_mode_and_do_not_skip_current_char(
			t_quote_mode *quote_mode)
{
	if (*quote_mode == ESCAPED)
		*quote_mode = UNQUOTED;
	else if (*quote_mode == DOUBLE_QUOTED_AND_ESCAPED)
		*quote_mode = DOUBLE_QUOTED;
	else
		return (false);
	return (true);
}
