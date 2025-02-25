/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:29:56 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 11:45:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../lex.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "./token_utils.h"

bool	start_token(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_token *(*create_token_of_correct_type)(
				t_input_tracker *input_tracker,
				bool *out_of_memory))
{
	t_token	*new_token;

	delimit_last_token_if_exists(input_tracker,
		get_last_token(tokens_with_status->tokens),
		&tokens_with_status->out_of_memory);
	if (tokens_with_status->out_of_memory)
		return (false);
	new_token
		= create_token_of_correct_type(input_tracker,
			&tokens_with_status->out_of_memory);
	if (tokens_with_status->out_of_memory)
		return (false);
	if (!ft_list_append(tokens_with_status->tokens, new_token))
	{
		destroy_token(new_token);
		tokens_with_status->out_of_memory = true;
		return (false);
	}
	return (true);
}
