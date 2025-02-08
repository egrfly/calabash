/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_operator_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:03:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 06:26:51 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../lex.h"
#include "./token_lifecycle.h"

static bool	set_operator_specific_properties(t_token *token)
{
	token->type = OPERATOR;
	return (true);
}

t_token	*create_operator_token(
			t_input_tracker *input_tracker,
			bool *has_error)
{
	return (create_token(input_tracker,
			set_operator_specific_properties,
			has_error));
}
