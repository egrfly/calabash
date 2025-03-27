/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_split_fields.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:02:08 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/27 16:47:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_string.h"
#include "../../lex/lex.h"
#include "../expand.h"
#include "../quote_mode_utils/quote_mode_utils.h"

static void	increment_field_count_if_field_len_nonzero(
				size_t field_len,
				size_t *field_count)
{
	if (field_len > 0)
		(*field_count)++;
}

size_t	count_split_fields(
			char *str)
{
	t_quote_mode	quote_mode;
	size_t			field_count;
	size_t			field_len;
	size_t			i;

	quote_mode = UNQUOTED;
	field_count = 0;
	field_len = 0;
	i = 0;
	while (str[i])
	{
		if (!update_quote_mode_based_on_current_char(&str[i], NOT_HEREDOC,
				&quote_mode) && quote_mode == UNQUOTED && ft_isspace(str[i]))
		{
			increment_field_count_if_field_len_nonzero(field_len, &field_count);
			field_len = 0;
		}
		else
			field_len++;
		i++;
	}
	increment_field_count_if_field_len_nonzero(field_len, &field_count);
	return (field_count);
}
