/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_var_and_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:47:51 by aistok            #+#    #+#             */
/*   Updated: 2025/03/22 13:20:12 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expansions.h"

void	destroy_var_and_value(void *var_and_value)
{
	t_var_and_value *node_value;

	node_value = (t_var_and_value *)var_and_value;
	if (node_value->var_name_was_malloced)
	{
		// ft_printf("Destroying: var_name = %s\n", node_value->var_name);
		free(node_value->var_name);
		node_value->var_name = NULL;
		node_value->var_name_was_malloced = false;
	}
	if (node_value->var_value_was_malloced)
	{
		// ft_printf("Destroying: var_value = %s\n", node_value->var_value);
		free(node_value->var_value);
		node_value->var_value = NULL;
		node_value->var_value_was_malloced = false;
	}
	// ft_printf("Destroying: node\n");
	free(node_value);
}
