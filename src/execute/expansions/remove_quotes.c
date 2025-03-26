/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:55:36 by aistok            #+#    #+#             */
/*   Updated: 2025/03/26 04:08:05 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "./expansions.h"

/*
 *	FOR FUTURE:
 *	if this function will only remove quotes from the beginning and the end of
 *	the string, then it could be simplified / "optimized", by calloc-ing
 *	ft_strlen(str) - 2 + 1 bytes!!!
 */
char	*remove_quotes(char *str)
{
	char	opening_quote;
	char	*quote_free_str;
	int		i;
	int		j;

	quote_free_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	// if (!quote_free_str)
	// 	return (NULL); //???
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
