/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exported_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:15:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 15:18:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

t_list	*get_exported_vars(
			t_list *vars)
{
	t_list		*exported_vars;
	t_list_node	*current_var_node;

	exported_vars = ft_list_init();
	if (!exported_vars)
		return (NULL);
	current_var_node = vars->first;
	while (current_var_node)
	{
		if (!ft_list_append(exported_vars, current_var_node->value))
			return (ft_list_destroy(exported_vars, NULL), NULL);
		current_var_node = current_var_node->next;
	}
	exported_vars->size = vars->size;
	return (exported_vars);
}
