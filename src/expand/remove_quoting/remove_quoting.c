/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quoting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:54:42 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/27 13:15:24 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_string.h"
#include "../../lex/lex.h"

static void	update_quote_mode_and_increment_shift(
				t_quote_mode *quote_mode,
				t_quote_mode new_quote_mode,
				size_t *shift)
{
	*quote_mode = new_quote_mode;
	(*shift)++;
}

static void	update_quote_mode_and_shift_based_on_current_char(
				char *c,
				bool is_heredoc,
				t_quote_mode *quote_mode,
				size_t *shift)
{
	if (*quote_mode == UNQUOTED && *c == '\\')
		update_quote_mode_and_increment_shift(quote_mode, ESCAPED, shift);
	else if (*quote_mode == UNQUOTED && *c == '\'')
		update_quote_mode_and_increment_shift(quote_mode, SINGLE_QUOTED, shift);
	else if (*quote_mode == UNQUOTED && *c == '\"')
		update_quote_mode_and_increment_shift(quote_mode, DOUBLE_QUOTED, shift);
	else if (*quote_mode == DOUBLE_QUOTED && *c == '\\'
		&& *(c + 1) && ft_strchr("$`\"\\", *(c + 1)))
		update_quote_mode_and_increment_shift(quote_mode,
			DOUBLE_QUOTED_AND_ESCAPED, shift);
	else if (*quote_mode == ESCAPED)
		*quote_mode = UNQUOTED;
	else if (*quote_mode == SINGLE_QUOTED && *c == '\'')
		update_quote_mode_and_increment_shift(quote_mode, UNQUOTED, shift);
	else if (*quote_mode == DOUBLE_QUOTED && *c == '\"' && !is_heredoc)
		update_quote_mode_and_increment_shift(quote_mode, UNQUOTED, shift);
	else if (*quote_mode == DOUBLE_QUOTED_AND_ESCAPED)
		*quote_mode = DOUBLE_QUOTED;
}

bool	remove_quoting(
			char *str,
			bool is_heredoc)
{
	t_quote_mode	quote_mode;
	size_t			shift;
	size_t			i;

	if (is_heredoc)
		quote_mode = DOUBLE_QUOTED;
	else
		quote_mode = UNQUOTED;
	shift = 0;
	i = 0;
	while (str[i])
	{
		str[i - shift] = str[i];
		update_quote_mode_and_shift_based_on_current_char(&str[i], is_heredoc,
			&quote_mode, &shift);
		i++;
	}
	str[i - shift] = '\0';
	return (shift > 0);
}
