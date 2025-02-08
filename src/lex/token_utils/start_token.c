/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:29:56 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 06:00:37 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../lex.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "./token_utils.h"

bool	start_token(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_token *(*create_token_of_correct_type)(
				t_input_tracker *input_tracker,
				bool *has_error),
			bool *has_error)
{
	t_token	*new_token;

	delimit_last_token_if_exists(input_tracker,
		get_last_token(tokens),
		has_error);
	if (*has_error)
		return (false);
	new_token = create_token_of_correct_type(input_tracker, has_error);
	if (*has_error)
		return (false);
	if (!ft_list_append(tokens, new_token))
	{
		destroy_token(new_token);
		*has_error = true;
		return (false);
	}
	return (true);
}
