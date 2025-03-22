/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_var_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:50:05 by aistok            #+#    #+#             */
/*   Updated: 2025/03/22 13:19:56 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "./expansions.h"

static int	char_allowed_for_start_of_var_name(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

static int	char_allowed_for_var_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
 *	If a variable name with length > 0 is found, will malloc and
 *	return A COPY for the portion from str.
 */
size_t	get_next_var_name(
			char *str,
			size_t position,
			char **var_name)
{
	size_t	var_len;
	size_t	i;

	i = position;
	if (str[i] && char_allowed_for_start_of_var_name(str[i]))
	{
		if (str[i] == '?' && i > 0 && str[i - 1] == '$')
			i++;
		else
			while (str[i] && char_allowed_for_var_name(str[i]))
				i++;
	}
	var_len = i - position;
	if (var_len)
	{
		*var_name = calloc(var_len + 1, sizeof(char));
		if (!*var_name)
			*var_name = NULL;
		else
			ft_memcpy(*var_name, &str[position], var_len);
	}
	else
		*var_name = NULL;
	return (var_len);
}
