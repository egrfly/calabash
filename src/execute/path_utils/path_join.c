/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:27:25 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 19:28:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"

char	*path_join(
			char *base,
			char *command_name)
{
	char	*joined_path;

	joined_path = malloc(sizeof(char)
			* (ft_strlen(base) + ft_strlen("/") + ft_strlen(command_name) + 1));
	if (!joined_path)
		return (NULL);
	ft_strcpy(joined_path, base);
	ft_strcat(joined_path, "/");
	ft_strcat(joined_path, command_name);
	return (joined_path);
}
