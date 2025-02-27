/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_to_new_word_token_if_necessary.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:33:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/27 20:01:06 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../lex.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "./token_utils.h"

bool	advance_to_new_word_token_if_necessary(
			t_input_tracker *input_tracker,
			t_token **last_token,
			t_tokens_with_status *tokens_with_status)
{
	if (!*last_token || (*last_token)->is_delimited)
	{
		start_token(input_tracker, tokens_with_status, create_word_token);
		if (tokens_with_status->out_of_memory)
			return (false);
		*last_token = get_last_token(tokens_with_status->tokens);
	}
	return (true);
}
