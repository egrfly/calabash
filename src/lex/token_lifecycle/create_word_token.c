/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:40:32 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 22:23:02 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_string.h"
#include "../lex.h"
#include "./token_lifecycle.h"

static bool	set_word_specific_properties(t_token *token)
{
	token->type = TYPE_WORD;
	token->content.word = ft_strdup("");
	return (token->content.word);
}

t_token	*create_word_token(
			t_input_tracker *input_tracker,
			bool *out_of_memory)
{
	return (create_token(input_tracker,
			set_word_specific_properties,
			out_of_memory));
}
