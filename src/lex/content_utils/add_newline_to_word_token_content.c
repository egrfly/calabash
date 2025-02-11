/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_newline_to_word_token_content.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:06:57 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/11 20:07:04 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "ft_string.h"
#include "../lex.h"

void	add_newline_to_word_token_content(
			t_token *token,
			bool *has_error)
{
	char	*existing_word;

	existing_word = token->content.word;
	token->content.word = ft_strjoin(token->content.word, "\n");
	if (!token->content.word)
		*has_error = true;
	free(existing_word);
}
