/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revert_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:08:12 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 21:52:05 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_list.h"
#include "../../parse/parse.h"

void	revert_redirections(
			t_list *redirections)
{
	t_list_node		*current_redirection_node;
	t_redirection	*current_redirection;

	if (!redirections)
		return ;
	current_redirection_node = redirections->last;
	while (current_redirection_node)
	{
		current_redirection = current_redirection_node->value;
		if (current_redirection->primary_reset_instruction.is_active)
		{
			dup2(current_redirection->primary_reset_instruction.original_fd,
				current_redirection->primary_reset_instruction.fd_to_reset);
			close(current_redirection->primary_reset_instruction.original_fd);
		}
		if (current_redirection->secondary_reset_instruction.is_active)
		{
			dup2(current_redirection->secondary_reset_instruction.original_fd,
				current_redirection->secondary_reset_instruction.fd_to_reset);
			close(current_redirection->secondary_reset_instruction.original_fd);
		}
		current_redirection_node = current_redirection_node->prev;
	}
}
