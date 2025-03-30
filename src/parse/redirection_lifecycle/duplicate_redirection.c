/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 02:16:19 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 02:35:19 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "../parse.h"

static void	copy_left_redirection(
				t_redirection *old_redirection,
				t_redirection *new_redirection)
{
	new_redirection->left_type = old_redirection->left_type;
	if (new_redirection->left_type == REDIRECTION_LEFT_NUMBER)
		new_redirection->left_content.number
			= old_redirection->left_content.number;
	else if (new_redirection->left_type == REDIRECTION_LEFT_REDIRECTION_WORD)
		new_redirection->left_content.redirection_word
			= ft_strdup(old_redirection->left_content.redirection_word);
}

static void	copy_right_redirection(
				t_redirection *old_redirection,
				t_redirection *new_redirection)
{
	new_redirection->right_type = old_redirection->right_type;
	if (new_redirection->right_type == REDIRECTION_RIGHT_NUMBER
		|| new_redirection->right_type == REDIRECTION_RIGHT_NUMBER_DASH)
		new_redirection->right_content.number
			= old_redirection->right_content.number;
	else if (new_redirection->right_type == REDIRECTION_RIGHT_WORD)
		new_redirection->right_content.word
			= ft_strdup(old_redirection->right_content.word);
}

static void	copy_reset_instruction(
				t_redirection_reset_instruction *old_reset_instruction,
				t_redirection_reset_instruction *new_reset_instruction)
{
	new_reset_instruction->is_active = old_reset_instruction->is_active;
	if (new_reset_instruction->is_active)
	{
		new_reset_instruction->original_fd = old_reset_instruction->original_fd;
		new_reset_instruction->fd_to_reset = old_reset_instruction->fd_to_reset;
	}
}

t_redirection	*duplicate_redirection(
					t_redirection *redirection)
{
	t_redirection	*new_redirection;

	new_redirection = ft_calloc(1, sizeof(t_redirection));
	if (!new_redirection)
		return (NULL);
	copy_left_redirection(redirection, new_redirection);
	new_redirection->operator = redirection->operator;
	copy_right_redirection(redirection, new_redirection);
	new_redirection->heredoc_delimiter_involved_quoting
		= redirection->heredoc_delimiter_involved_quoting;
	copy_reset_instruction(&redirection->primary_reset_instruction,
		&new_redirection->primary_reset_instruction);
	copy_reset_instruction(&redirection->secondary_reset_instruction,
		&new_redirection->secondary_reset_instruction);
	return (new_redirection);
}
