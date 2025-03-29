/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat_with_escapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:13:04 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 18:44:50 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

char	*strcat_with_escapes(
			char *dest,
			const char *src,
			bool is_double_quoted)
{
	size_t	i;
	size_t	j;
	size_t	quoting_char_count;

	i = 0;
	while (dest[i])
		i++;
	quoting_char_count = 0;
	j = 0;
	while (src[j])
	{
		if (src[j] == '\\' || src[j] == '\"'
			|| (src[j] == '\'' && !is_double_quoted))
		{
			dest[i + j + quoting_char_count] = '\\';
			quoting_char_count++;
		}
		dest[i + j + quoting_char_count] = src[j];
		j++;
	}
	dest[i + j + quoting_char_count] = '\0';
	return (dest);
}
