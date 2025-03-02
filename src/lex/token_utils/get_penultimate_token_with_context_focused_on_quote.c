/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_penultimate_token_with_context_focused_        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:12:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/02 04:58:26 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../lex.h"
#include "../context_utils/context_utils.h"

/**
 * @brief Adjusts start of existing token context to focus on the quote
 * rather than the first character.
 * 
 * @note Three cases:
 * 
 * 1. There is no existing ellipsis and no need to add a new one.
 *    In this case, simply note that we want to erase everything in the existing
 *    context from the quote mark onwards.
 * 
 * 2. There is no existing ellipsis and we need to add a new one.
 *    In this case, move the part of the context we are interested in keeping to
 *    three characters after the start of the context to make space for the
 *    ellipsis, copy in the ellipsis, then mark everything from the quote mark
 *    onwards for erasure.
 * 
 * 3. There is an existing ellipsis (which we need to keep).
 *    In this case, move the part of the context we are interested in keeping to
 *    three characters after the start of the context to avoid touching the
 *    ellipsis, then mark everything from the quote mark onwards for erasure.
 * 
 * @param token the token to adjust the context for
 */
static void	reuse_start_of_existing_token_context(
				t_token *token)
{
	int	bzero_from_index;

	if (token->last_opening_quote_index_in_line <= MAX_LEADING_CONTEXT_LENGTH)
		bzero_from_index = token->last_opening_quote_index_in_line;
	else if (token->start_index_in_start_line <= MAX_LEADING_CONTEXT_LENGTH)
	{
		ft_memmove(&token->surrounding_context[ELLIPSIS_LENGTH],
			&token->surrounding_context[token->last_opening_quote_index_in_line
			- MAX_LEADING_CONTEXT_LENGTH],
			MAX_LEADING_CONTEXT_LENGTH);
		ft_memcpy(token->surrounding_context, "...", ELLIPSIS_LENGTH);
		bzero_from_index = ELLIPSIS_LENGTH + MAX_LEADING_CONTEXT_LENGTH;
	}
	else
	{
		ft_memmove(&token->surrounding_context[ELLIPSIS_LENGTH],
			&token->surrounding_context[token->start_index_in_context
			+ token->last_opening_quote_index_in_word_content_line
			- MAX_LEADING_CONTEXT_LENGTH],
			MAX_LEADING_CONTEXT_LENGTH);
		bzero_from_index = ELLIPSIS_LENGTH + MAX_LEADING_CONTEXT_LENGTH;
	}
	ft_bzero(&token->surrounding_context[bzero_from_index],
		sizeof(token->surrounding_context) - bzero_from_index);
}

static void	overwrite_start_of_existing_token_context(
				t_token *token)
{
	char	*quote_line;

	ft_bzero(token->surrounding_context, sizeof(token->surrounding_context));
	quote_line = &token->content.word[
		token->last_opening_quote_line_start_index_in_word_content];
	add_token_leading_context(token, quote_line,
		token->last_opening_quote_index_in_word_content_line);
}

/**
 * @brief Rewrites token context to focus on the quote rather than the first
 * character.
 * 
 * @note Steps:
 * 
 * 1. Adds leading token context, either by adjusting existing context if quote
 *    is near the start of the first line of the token content, or by adding new
 *    context otherwise.
 * 
 * 2. Adds the quote mark to the context (length 1, never truncated).
 * 
 * 3. Adds the trailing context (which will always consist solely of characters
 *    from the token content, since the quote within the content was never
 *    closed and therefore no further contentful tokens were generated).
 * 
 * @param token the token to rewrite the context for
 */
static void	rewrite_token_context_to_focus_on_quote(
				t_token *token)
{
	char	*quote_line;

	if (token->last_opening_quote_line_index == token->start_line_index
		&& token->last_opening_quote_index_in_word_content_line
		< MAX_LEADING_CONTEXT_LENGTH)
		reuse_start_of_existing_token_context(token);
	else
		overwrite_start_of_existing_token_context(token);
	token->start_index_in_context = ft_strlen(token->surrounding_context);
	quote_line = &token->content.word[
		token->last_opening_quote_line_start_index_in_word_content];
	ft_strncat(token->surrounding_context,
		&quote_line[token->last_opening_quote_index_in_word_content_line], 1);
	token->length_in_context = 1;
	token->context_was_truncated = false;
	add_token_trailing_context(token, quote_line,
		token->last_opening_quote_index_in_word_content_line + 1);
}

/**
 * @brief Adjusts the token start position to focus on the quote.
 * 
 * @note Not ideal since the token start position no longer reflects the
 * position of the first character of the token, but rather the position of the
 * quote. However, this is advantageous when printing error messages about
 * early termination, since it means the relevant unclosed quote can be
 * pinpointed more easily.
 * 
 * @param token the token to adjust the start position for
 */
static void	adjust_token_start_position_to_focus_on_quote(
				t_token *token)
{
	token->start_index_in_start_line = token->last_opening_quote_index_in_line;
	token->start_line_index = token->last_opening_quote_line_index;
}

/**
 * @brief Gets the penultimate token, adjusts the token context and start
 * position to focus on the quote inside, then returns the token.
 * 
 * @param tokens the token list to get the penultimate member of
 */
t_token	*get_penultimate_token_with_context_focused_on_quote(
			t_list *tokens)
{
	t_token		*token;

	if (tokens->last && tokens->last->prev)
	{
		token = tokens->last->prev->value;
		rewrite_token_context_to_focus_on_quote(token);
		adjust_token_start_position_to_focus_on_quote(token);
		return (token);
	}
	return (NULL);
}
