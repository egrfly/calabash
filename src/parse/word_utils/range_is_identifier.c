/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_is_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:36:02 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:02:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_ctype.h"

bool	range_is_identifier(char *word, unsigned int start, unsigned int end)
{
	unsigned int	i;

	i = 0;
	while (i < start && word[i])
		i++;
	if (i >= end || !word[i] || !(ft_isalpha(word[i]) || word[0] == '_'))
		return (false);
	i++;
	while (i < end && word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
		i++;
	return (i == end);
}
