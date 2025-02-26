/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 04:04:46 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 08:38:42 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stdio.h"
#include "ft_string.h"
#include "../lex/lex.h"
#include "./debug.h"

static const
	char
	*g_token_type_descriptors[] = {
[TYPE_WORD] = "word",
[TYPE_OPERATOR] = "operator",
[TYPE_NEWLINE] = "newline",
[TYPE_WHITESPACE] = "whitespace",
[TYPE_END_OF_INPUT] = "end of input",
};

void	print_tokens(t_list *tokens)
{
	t_list_node	*current_node;
	t_token		*current_token;

	current_node = tokens->first;
	while (current_node)
	{
		current_token = current_node->value;
		ft_printf("Type: %-12s | line index %d, char index %d\n",
			g_token_type_descriptors[current_token->type],
			current_token->start_line_index,
			current_token->start_index_in_start_line);
		if (current_token->type == TYPE_WORD)
			ft_printf("Word content: `%s`\n", current_token->content.word);
		if (current_token->type == TYPE_OPERATOR)
			ft_printf("Operator content: `%s`\n",
				get_operator_symbol(current_token->content.operator));
		ft_printf("Context: %s\n%*s%.*s\n",
			current_token->surrounding_context,
			current_token->start_index_in_context + ft_strlen("Context: "),
			"",
			current_token->length_in_context,
			"^^^^^^^^^^");
		current_node = current_node->next;
	}
}
