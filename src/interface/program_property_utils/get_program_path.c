/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:46:54 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/11 02:13:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_string.h"
#include "../../main.h"
#include "../../execute/path_utils/path_utils.h"
#include "../interface.h"

static char	*get_path_var_from_envp(
				char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strstarts(envp[i], "PATH="))
			return (&envp[i][ft_strlen("PATH=")]);
		i++;
	}
	return (NULL);
}

static void	case_by_case_set_program_path(
				char *program_path,
				char *new_program_name,
				char **envp)
{
	char	*current_dir;
	char	*temp_program_path;

	if (ft_strstarts(new_program_name, "/"))
		ft_strlcat(program_path, new_program_name, PATH_MAX + 1);
	else if (ft_strchr(new_program_name, '/'))
	{
		current_dir = getcwd(NULL, 0);
		if (current_dir)
		{
			ft_strlcat(program_path, current_dir, PATH_MAX + 1);
			ft_strlcat(program_path, "/", PATH_MAX + 1);
			ft_strlcat(program_path, new_program_name, PATH_MAX + 1);
		}
		free(current_dir);
	}
	else
	{
		get_full_command_path(&temp_program_path, new_program_name,
			get_path_var_from_envp(envp));
		if (temp_program_path)
			ft_strlcat(program_path, temp_program_path, PATH_MAX + 1);
		free(temp_program_path);
	}
}

static char	*access_program_path(
				t_access_mode mode,
				char *new_program_name,
				char **envp)
{
	static char	program_path[PATH_MAX + 1];

	if (mode == SET && !ft_strcmp(program_path, ""))
		case_by_case_set_program_path(program_path, new_program_name, envp);
	else if (mode == GET)
		return (program_path);
	return (NULL);
}

void	set_program_path(
			char *new_program_name,
			char **envp)
{
	access_program_path(SET, new_program_name, envp);
}

char	*get_program_path(void)
{
	return (access_program_path(GET, NO_ARG, NO_ARG));
}
