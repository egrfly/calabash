/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_from_values.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:18:25 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 09:26:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"

t_list	*get_list_from_values(
			char **values)
{
	t_list	*list;
	int		i;
	char	*current_value;

	list = ft_list_init();
	if (!list)
		return (NULL);
	i = 0;
	while (values[i])
	{
		current_value = ft_strdup(values[i]);
		if (!current_value)
			return (ft_list_destroy(list, free), NULL);
		if (!ft_list_append(list, current_value))
		{
			free(current_value);
			return (ft_list_destroy(list, free), NULL);
		}
		i++;
	}
	return (list);
}
