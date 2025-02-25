/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_newline_to_word_token_content.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:06:57 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 12:18:54 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "ft_string.h"
#include "../lex.h"

void	add_newline_to_word_token_content(
			t_token *token,
			bool *out_of_memory)
{
	char	*existing_word;

	existing_word = token->content.word;
	if (!existing_word)
		return ;
	token->content.word = ft_strjoin(token->content.word, "\n");
	if (!token->content.word)
		*out_of_memory = true;
	free(existing_word);
}
