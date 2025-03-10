/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:20:09 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 13:28:57 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../parse/word_utils/word_utils.h"
#include "./var_utils.h"

void	remove_var(
			char *var_name,
			t_list *vars)
{
	t_list_node	*current_var_node;
	char		*current_var;

	if (!is_identifier(var_name))
		return ;
	current_var_node = vars->first;
	while (current_var_node)
	{
		current_var = current_var_node->value;
		if (vars_have_same_name(var_name, current_var))
		{
			ft_list_removenode(vars, current_var_node);
			return ;
		}
		current_var_node = current_var_node->next;
	}
}
