/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list_from_envp.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:18:25 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 19:19:15 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"

t_list	*get_env_list_from_envp(char **envp)
{
	t_list	*env;
	int		i;
	char	*current_value;

	env = ft_list_init();
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		current_value = ft_strdup(envp[i]);
		if (!current_value)
			return (ft_list_destroy(env, free), NULL);
		if (!ft_list_append(env, current_value))
		{
			free(current_value);
			return (ft_list_destroy(env, free), NULL);
		}
		i++;
	}
	return (env);
}
