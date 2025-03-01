/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tokens_with_status.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:09:07 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/01 02:37:44 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../lex.h"

void	destroy_tokens_with_status(
			t_tokens_with_status *tokens_with_status)
{
	if (!tokens_with_status)
		return ;
	if (tokens_with_status->tokens)
		ft_list_destroy(tokens_with_status->tokens,
			(t_action_func)destroy_token);
	free(tokens_with_status);
}
