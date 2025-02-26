/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_with_status.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:05:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 15:07:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_stdlib.h"
#include "../lex.h"

t_tokens_with_status	*create_tokens_with_status(void)
{
	t_tokens_with_status	*tokens_with_status;

	tokens_with_status
		= ft_calloc(sizeof(t_tokens_with_status), 1);
	if (!tokens_with_status)
		return (NULL);
	tokens_with_status->tokens = ft_list_init();
	if (!tokens_with_status->tokens)
	{
		free(tokens_with_status);
		return (NULL);
	}
	return (tokens_with_status);
}
