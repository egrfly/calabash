/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 20:33:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/list_utils/list_utils.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../execution_funcs/execution_funcs.h"
#include "../variable_utils/variable_utils.h"
#include "./builtins.h"

#define OLDPWD_NOT_SET -100
#define HOME_DIR_NOT_SET -200

#define PATH_FROM_HOME_VAR true
#define PATH_NOT_FROM_HOME_VAR false

int	check_dir_access(const char *path)
{
	DIR	*directory;
	int	saved_errno;

	if (!path)
		return (ENOENT);
	directory = opendir(path);
	if (!directory)
		return (errno);
	saved_errno = errno;
	closedir(directory);
	return (saved_errno);
}

void	print_error(
			char *program_name, char *command_name,
			char *path, char *error_message)
{
	if (ft_strcmp(path, "HOME") == 0 || ft_strcmp(path, "OLDPWD") == 0)
		ft_dprintf(STDERR_FILENO, "%s: %s: %s %s\n",
			program_name, command_name, path, error_message);
	else
		ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n",
			program_name, command_name, path, error_message);
}

void	internal_chdir(
			const char *target_path, char *current_dir, char **oldpwd)
{
	chdir(target_path);
	free(*oldpwd);
	*oldpwd = current_dir;
}

int	try_change_dir_to(
		const char *target_path, char **oldpwd, bool target_path_from_home_var)
{
	char	*current_dir;
	int		dir_access_test;

	current_dir = getcwd(NULL, 0);
	if (ft_strcmp(target_path, "-") == 0)
	{
		if (!*oldpwd)
			return (free(current_dir), OLDPWD_NOT_SET);
		dir_access_test = check_dir_access(*oldpwd);
		if (dir_access_test > 0)
			return (free(current_dir), errno);
		internal_chdir(*oldpwd, current_dir, oldpwd);
	}
	else
	{
		dir_access_test = check_dir_access(target_path);
		if (dir_access_test)
		{
			if (target_path_from_home_var)
				return (free(current_dir), HOME_DIR_NOT_SET);
			return (free(current_dir), errno);
		}
		internal_chdir(target_path, current_dir, oldpwd);
	}
	return (SUCCESS);
}

int	builtin_cd(
		const char **argv, t_program_vars *program_vars)
{
	static char	*oldpwd = NULL;
	char		*home_dir;
	int			error_no;

	// Check
	home_dir = ft_strdup(get_variable_value(program_vars->env, "HOME"));
	if (argv[1])
	{
		error_no = try_change_dir_to(argv[1], &oldpwd, PATH_NOT_FROM_HOME_VAR);
		if (error_no == OLDPWD_NOT_SET)
			return (free(home_dir), print_error(get_program_name(),
					(char *)argv[0], "OLDPWD", "not set"), GENERAL_FAILURE);
	}
	else
	{
		error_no = try_change_dir_to(home_dir, &oldpwd, PATH_FROM_HOME_VAR);
		if (error_no == HOME_DIR_NOT_SET)
			return (free(home_dir), print_error(get_program_name(),
					(char *)argv[0], "HOME", "not set"), GENERAL_FAILURE);
	}
	if (error_no)
		return (free(home_dir), print_error(get_program_name(), (char *)argv[0],
				(char *)argv[1], strerror(error_no)), GENERAL_FAILURE);
	return (free(home_dir), SUCCESS);
}
