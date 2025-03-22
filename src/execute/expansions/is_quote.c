/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:53:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/22 17:01:59 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "./expansions.h"

bool	is_quote(
			char c,
			t_quote_types quote_type)
{
	if (quote_type == QUOTE_ANY)
		return (c == '\'' || c == '"');
	if (quote_type == QUOTE_SINGLE)
		return (c == '\'');
	if (quote_type == QUOTE_DOUBLE)
		return (c == '"');
	return (false);
}
