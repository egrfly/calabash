/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_whitespace_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:39:13 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 06:26:51 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../lex.h"
#include "./token_lifecycle.h"

static bool	set_whitespace_specific_properties(t_token *token)
{
	token->type = WHITESPACE;
	return (true);
}

t_token	*create_whitespace_token(
			t_input_tracker *input_tracker,
			bool *has_error)
{
	return (create_token(input_tracker,
			set_whitespace_specific_properties,
			has_error));
}
