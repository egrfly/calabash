/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_identifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:33:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/14 00:36:15 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_ctype.h"

bool	is_identifier(char *word)
{
	int	i;

	if (!word[0] || !(ft_isalpha(word[0]) || word[0] == '_'))
		return (false);
	i = 1;
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
		i++;
	return (!word[i]);
}
