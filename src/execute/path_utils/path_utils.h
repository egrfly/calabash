/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:28:38 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 20:37:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_UTILS_H
# define PATH_UTILS_H

# include <stdbool.h>

bool	get_full_command_path(
			char **path,
			char *command,
			char *path_var);
char	**get_path_options(
			char *path_var);
char	*path_join(
			char *base,
			char *command_name);

#endif
