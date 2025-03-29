/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:41:03 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 18:43:19 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../lex/lex.h"
#include "../char_utils/char_utils.h"
#include "./quote_mode_utils.h"

bool	should_expand(
			char *str,
			t_quote_mode *quote_mode,
			t_quote_mode base_quote_mode)
{
	return (!update_quote_mode_based_on_current_char(str,
			quote_mode, base_quote_mode)
		&& (*quote_mode == UNQUOTED || *quote_mode == DOUBLE_QUOTED)
		&& *str == '$' && is_expandable_char(*(str + 1)));
}
