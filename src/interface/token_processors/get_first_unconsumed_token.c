/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_unconsumed_token.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:19:33 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 15:20:26 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../../lex/lex.h"

t_token	*get_first_unconsumed_token(
			t_list *tokens)
{
	t_list_node	*token_node;
	t_token		*token;

	token_node = tokens->first;
	while (token_node)
	{
		token = token_node->value;
		if (!token->has_been_consumed_at_some_point)
			return (token);
		token_node = token_node->next;
	}
	return (NULL);
}
