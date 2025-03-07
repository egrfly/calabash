/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/07 08:37:15 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TODO: these includes need cleaning */
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "builtins.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "ft_stdlib.h"

#define OLDPWD_NOT_SET -100
#define HOME_DIR_NOT_SET -200
#define PATH_FROM_HOME_VAR true
#define PATH_NOT_FROM_HOME_VAR false

/* TODO: this function can go in some other file? Utils maybe? List utils? */
char	*get_line_starting_with(
			t_list *list, char *start_str, char *after_char)
{
	t_list_node	*list_node;

	if (!list || !start_str)
		return (NULL);
	list_node = list->first;
	while (list_node)
	{
		if (ft_strstarts(list_node->value, start_str))
		{
			if (!after_char)
				return (ft_strdup(list_node->value));
			if (!ft_strchr(list_node->value, after_char[0]))
				return (NULL);
			return (ft_strdup(&ft_strchr(list_node->value, after_char[0])[1]));
		}
		list_node = list_node->next;
	}
	return (NULL);
}

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

void	internal_chdir(const char *new_path, char *old_path, char **oldpwd)
{
	chdir(new_path);
	free(*oldpwd);
	*oldpwd = old_path;
}

int	try_change_dir_to(
		const char *target_path, char **oldpwd, bool path_from_home_var)
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
			if (path_from_home_var)
				return (free(current_dir), HOME_DIR_NOT_SET);
			return (free(current_dir), errno);
		}
		internal_chdir(target_path, current_dir, oldpwd);
	}
	return (SUCCESS);
}

int	builtin_cd(
		const char **argv, t_program_name_and_env *program_name_and_env)
{
	static char	*oldpwd = NULL;
	char		*home_dir;
	int			error_no;

	home_dir = get_line_starting_with(program_name_and_env->env, "HOME", "=");
	if (argv[1])
	{
		error_no = try_change_dir_to(argv[1], &oldpwd, PATH_NOT_FROM_HOME_VAR);
		if (error_no == OLDPWD_NOT_SET)
			return (print_error(program_name_and_env->name,
					(char *)argv[0], "OLDPWD", "not set"), GENERAL_FAILURE);
	}
	else if (home_dir)
	{
		error_no = try_change_dir_to(home_dir, &oldpwd, PATH_FROM_HOME_VAR);
		if (error_no == HOME_DIR_NOT_SET)
			return (print_error(program_name_and_env->name,
					(char *)argv[0], "HOME", "not set"), GENERAL_FAILURE);
	}
	if (error_no)
		return (print_error(program_name_and_env->name, (char *)argv[0],
				(char *)argv[1], strerror(error_no)), GENERAL_FAILURE);
	return (SUCCESS);
}
