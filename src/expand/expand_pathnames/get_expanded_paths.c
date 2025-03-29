/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expanded_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:46:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 16:01:01 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include "ft_list.h"
#include "ft_stdio.h"
	#include "../../interface/interface.h"
#include "../../interface/program_property_utils/program_property_utils.h"

bool	get_all_entries_in_dir(char *path, t_list **entries)
{
	DIR				*dir_stream;
	struct dirent	*raw_entries;

	if (!path)
		return (false);
	dir_stream = opendir(path);
	if (!dir_stream)
		// return (ft_dprintf(STDERR_FILENO, "%s: %s\n",
		// 	get_program_name(), strerror(errno)), false);
		return (false);
	errno = 0;
	raw_entries = readdir(dir_stream);
	if (!raw_entries && errno == 0)
		return (false);
	if (!*entries)
		*entries = ft_list_init();
	if (!*entries)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
			get_program_name()),
			ft_list_destroy(*entries, free), false);
	while (raw_entries)
	{
		ft_printf("Entry: %s\n", raw_entries->d_name);
		errno = 0;
		raw_entries = readdir(dir_stream);
		if (!raw_entries && errno == 0)
			return (false);
	}
	closedir(dir_stream);
	return (true);
}

bool	get_expanded_paths_from_str(char *str)
{
	//..
}

/*
 *	Optional:
 *	else if (str[i] == '*' || str[i] == '?' || str[i] == '[')
 */
bool	need_perform_expand_pathnames(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

t_list	*get_expand_pathnames(char *str)
{
	t_list	*expanded_paths;
	t_list	*expanded_paths_from_str;
	char	*str_copy;

	expanded_paths = ft_list_init();
	if (!expanded_paths)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
			get_program_name()), NULL);
	if (!need_perform_expand_pathnames(str))
	{
		str_copy = ft_strdup(str);
		if (!str_copy)
			return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()),
				ft_list_destroy(expanded_paths, free), NULL);
		ft_list_append(expanded_paths, str_copy);
	}
	else
	{
		expanded_paths_from_str = get_expanded_paths_from_str();
		if (!expanded_paths_from_str)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
			get_program_name()),
			ft_list_destroy(expanded_paths, free), NULL);
		ft_list_merge(expanded_paths, expanded_paths_from_str);
	}
	return (expanded_paths);
}
