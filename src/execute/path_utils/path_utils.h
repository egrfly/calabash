/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:28:38 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 17:51:08 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_UTILS_H
# define PATH_UTILS_H

# include <stdbool.h>
# include "ft_list.h"

# define ACCESS_SUCCESS 0
# define STAT_SUCCESS 0

bool	get_full_command_path(
			char **path,
			char *command,
			char *path_variable);
char	*get_path_variable(
			t_list *env);
char	*path_join(
			char *base,
			char *command_name);

#endif
