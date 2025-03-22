/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:55:36 by aistok            #+#    #+#             */
/*   Updated: 2025/03/22 17:09:32 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "./expansions.h"

char	*remove_quotes(char *str)
{
	char	opening_quote;
	char	*quote_free_str;
	int		i;
	int		j;

	quote_free_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	opening_quote = ' ';
	while (str[i])
	{
		if (is_quote(str[i], QUOTE_ANY) && !is_quote(opening_quote, QUOTE_ANY))
			opening_quote = str[i];
		else if (is_quote(opening_quote, QUOTE_ANY) && str[i] == opening_quote)
			opening_quote = ' ';
		else
		{
			quote_free_str[j] = str[i];
			j++;
		}
		i++;
	}
	return (quote_free_str);
}
