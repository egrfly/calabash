/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_out_duplicate_assignments.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:51:00 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 09:53:18 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "./assignment_utils.h"

void	filter_out_duplicate_assignments(
			t_list *env)
{
	t_list_node	*current_env_node;
	t_list_node	*later_env_node;

	current_env_node = env->first;
	while (current_env_node)
	{
		later_env_node = current_env_node->next;
		while (later_env_node)
		{
			if (assignments_have_same_identifier(current_env_node->value,
					later_env_node->value))
			{
				ft_list_removenode(env, current_env_node);
				break ;
			}
			later_env_node = later_env_node->next;
		}
		current_env_node = current_env_node->next;
	}
}
