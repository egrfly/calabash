/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:57:40 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 20:46:01 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"

char	*get_path_variable(
			t_list *env)
{
	t_list_node	*env_node;

	env_node = env->first;
	while (env_node)
	{
		if (ft_strstarts(env_node->value, "PATH="))
			return (&ft_strchr(env_node->value, '=')[1]);
		env_node = env_node->next;
	}
	return (NULL);
}
