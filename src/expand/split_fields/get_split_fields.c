/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_split_fields.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:01:36 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/27 16:44:20 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_ctype.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../lex/lex.h"
#include "../expand.h"
#include "../quote_mode_utils/quote_mode_utils.h"

static bool	add_field_if_field_len_nonzero(
				size_t field_len,
				char *field_start,
				t_list *split_fields)
{
	char	*field;

	if (field_len > 0)
	{
		field = ft_strndup(field_start, field_len);
		if (!field)
		{
			ft_list_destroy(split_fields, free);
			return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
					get_program_name()), false);
		}
		if (!ft_list_append(split_fields, field))
		{
			free(field);
			ft_list_destroy(split_fields, free);
			return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
					get_program_name()), false);
		}
	}
	return (true);
}

t_list	*get_split_fields(
			char *str)
{
	t_list			*split_fields;
	t_quote_mode	quote_mode;
	size_t			field_len;
	size_t			i;

	split_fields = ft_list_init();
	if (!split_fields)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), NULL);
	quote_mode = UNQUOTED;
	field_len = 0;
	i = 0;
	while (str[i])
	{
		if (!update_quote_mode_based_on_current_char(&str[i], NOT_HEREDOC,
				&quote_mode) && quote_mode == UNQUOTED && ft_isspace(str[i]))
		{
			if (!add_field_if_field_len_nonzero(field_len, &str[i - field_len],
					split_fields))
				return (NULL);
			field_len = 0;
		}
		else
			field_len++;
		i++;
	}
	if (!add_field_if_field_len_nonzero(field_len, &str[i - field_len],
			split_fields))
		return (NULL);
	return (split_fields);
}
