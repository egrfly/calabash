/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expanded_pathnames.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:46:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 23:32:02 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../lex/lex.h"
#include "../quote_mode_utils/quote_mode_utils.h"
#include "./expand_pathnames.h"

static bool	try_match_current_char_and_advance(
				char **word,
				char **pattern,
				t_quote_mode *quote_mode,
				t_match_checkpoint *checkpoint)
{
	while (update_quote_mode_and_skip_current_char(*pattern, quote_mode))
		(*pattern)++;
	if (**word == '/' && *quote_mode == UNQUOTED)
		return (false);
	if (!(**pattern == '*' && *quote_mode == UNQUOTED) && **pattern == **word)
	{
		(*pattern)++;
		(*word)++;
	}
	else if (**pattern == '*' && *quote_mode == UNQUOTED)
	{
		checkpoint->latest_star = (*pattern)++;
		checkpoint->quote_mode_at_latest_star = *quote_mode;
		checkpoint->last_attempted_match_start = *word;
	}
	else if (checkpoint->latest_star)
	{
		*pattern = checkpoint->latest_star + 1;
		*quote_mode = checkpoint->quote_mode_at_latest_star;
		*word = ++checkpoint->last_attempted_match_start;
	}
	else
		return (false);
	update_quote_mode_and_do_not_skip_current_char(quote_mode);
	return (true);
}

static bool	matches_pattern(
				char *word,
				char *pattern)
{
	t_quote_mode		quote_mode;
	t_match_checkpoint	checkpoint;

	quote_mode = UNQUOTED;
	checkpoint.quote_mode_at_latest_star = UNQUOTED;
	checkpoint.latest_star = NULL;
	checkpoint.last_attempted_match_start = NULL;
	while (update_quote_mode_and_skip_current_char(pattern,
			&quote_mode))
		pattern++;
	if (*pattern != '.' && *word == '.')
		return (false);
	while (*word)
		if (!try_match_current_char_and_advance(&word, &pattern,
				&quote_mode, &checkpoint))
			return (false);
	while (update_quote_mode_and_skip_current_char(pattern, &quote_mode)
		|| (*pattern == '*' && quote_mode == UNQUOTED))
		pattern++;
	return (!*pattern);
}

static t_list	*get_all_entries_in_cwd(void)
{
	char			*current_dir;
	t_list			*entries;
	DIR				*dir_stream;
	struct dirent	*raw_entry;
	char			*entry_name;

	current_dir = getcwd(NULL, 0);
	entries = ft_list_init();
	dir_stream = opendir(current_dir);
	if (!current_dir || !entries || !dir_stream)
		return (free(current_dir), free(entries), NULL);
	free(current_dir);
	raw_entry = readdir(dir_stream);
	while (raw_entry)
	{
		entry_name = ft_strdup(raw_entry->d_name);
		if (!entry_name || !ft_list_append(entries, entry_name))
			return (ft_list_destroy(entries, free), closedir(dir_stream), NULL);
		raw_entry = readdir(dir_stream);
	}
	closedir(dir_stream);
	ft_list_sort(entries, ft_strcmp);
	return (entries);
}

static t_list	*get_expanded_paths_from_str(
					char *pattern)
{
	t_list		*entries;
	t_list_node	*entry_node;
	t_list_node	*next_entry_node;

	entries = get_all_entries_in_cwd();
	if (!entries)
		return (ft_list_init());
	entry_node = entries->first;
	while (entry_node)
	{
		next_entry_node = entry_node->next;
		if (!matches_pattern(entry_node->value, pattern))
		{
			ft_list_removenode(entries, entry_node);
			ft_list_delnode(entry_node, free);
		}
		entry_node = next_entry_node;
	}
	return (entries);
}

t_list	*get_expanded_pathnames(
			char *str)
{
	t_list	*expanded_paths;
	char	*new_str;

	if (ft_strchr(str, '*'))
	{
		expanded_paths = get_expanded_paths_from_str(str);
		if (!expanded_paths)
			return (NULL);
		if (expanded_paths->first)
			return (expanded_paths);
		else
			ft_list_destroy(expanded_paths, free);
	}
	expanded_paths = ft_list_init();
	new_str = ft_strdup(str);
	if (!expanded_paths || !new_str
		|| !ft_list_append(expanded_paths, new_str))
		return (free(new_str), ft_list_destroy(expanded_paths, free), NULL);
	return (expanded_paths);
}
