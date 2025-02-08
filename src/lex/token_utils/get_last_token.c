/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:12:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:41:55 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../lex.h"

t_token	*get_last_token(
			t_list *tokens)
{
	if (tokens->last)
		return (tokens->last->value);
	return (NULL);
}
