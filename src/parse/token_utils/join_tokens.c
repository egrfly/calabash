/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:13:12 by aistok            #+#    #+#             */
/*   Updated: 2025/03/08 22:17:55 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "../../lex/lex.h"
#include "../token_utils/token_utils.h"

void	join_tokens(
			t_list_node *current_token_node,
			t_tokens_with_status *next_line_tokens)
{
	set_token_type(current_token_node->value, TYPE_NEWLINE);
	ft_list_splicenodes(current_token_node, next_line_tokens->tokens->first);
	free(next_line_tokens);
}
