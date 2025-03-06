/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_command_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:30:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 17:51:23 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ft_string.h"
#include "./path_utils.h"

#define FOUND 1
#define NOT_FOUND 1
#define OUT_OF_MEMORY 0

static bool	keep_absolute_or_relative_path(
				char **path,
				char *command)
{
	*path = ft_strdup(command);
	return (*path);
}

static bool	use_regular_file(char **path, char *full_command_path)
{
	struct stat	stat_buffer;

	if (access(full_command_path, F_OK) == ACCESS_SUCCESS
		&& stat(full_command_path, &stat_buffer) == STAT_SUCCESS
		&& S_ISREG(stat_buffer.st_mode))
	{
		*path = full_command_path;
		return (true);
	}
	return (false);
}

bool	get_full_command_path(
			char **path,
			char *command,
			char *path_variable)
{
	char	**path_options;
	int		i;
	char	*full_command_path;

	if (ft_strchr(command, '/'))
		return (keep_absolute_or_relative_path(path, command));
	if (!path_variable)
		return (NOT_FOUND);
	path_options = ft_split(path_variable, ":");
	if (!path_options)
		return (OUT_OF_MEMORY);
	i = 0;
	while (path_options[i])
	{
		full_command_path = path_join(path_options[i], command);
		if (!full_command_path)
			return (ft_split_destroy(&path_options), OUT_OF_MEMORY);
		if (use_regular_file(path, full_command_path))
			return (ft_split_destroy(&path_options), FOUND);
		free(full_command_path);
		i++;
	}
	ft_split_destroy(&path_options);
	return (NOT_FOUND);
}
