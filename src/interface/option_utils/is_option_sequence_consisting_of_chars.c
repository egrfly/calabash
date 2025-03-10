/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_option_sequence_consisting_of_chars.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:33:36 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 10:35:58 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_string.h"

bool	is_option_sequence_consisting_of_chars(
			const char *argument,
			const char *charset)
{
	size_t	i;

	if (argument[0] == '-'
		&& argument[1]
		&& ft_strchr(charset, argument[1]))
	{
		i = 2;
		while (argument[i] && ft_strchr(charset, argument[i]))
			i++;
		if (!argument[i])
			return (true);
	}
	return (false);
}
