/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_with_escapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:12:25 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 12:12:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

size_t	strlen_with_escapes(
			char *str,
			bool is_double_quoted)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '\"'
			|| (str[i] == '\'' && !is_double_quoted))
			len++;
		len++;
		i++;
	}
	return (len);
}
