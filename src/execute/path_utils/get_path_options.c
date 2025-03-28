/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:19:35 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 23:50:17 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/list_utils/list_utils.h"
#include "../../expand/quote_mode_utils/quote_mode_utils.h"
#include "../../lex/lex.h"

static bool	add_path_option(
				char *path_var,
				size_t path_option_len,
				t_list *path_options_list)
{
	char	*path_option;

	if (path_option_len > 0)
		path_option = ft_strndup(path_var - path_option_len, path_option_len);
	else
		path_option = ft_strdup("./");
	if (!path_option || !ft_list_append(path_options_list, path_option))
		return (free(path_option), false);
	return (true);
}

static bool	populate_path_options_list(
				char *path_var,
				t_list *path_options_list)
{
	t_quote_mode	quote_mode;
	size_t			path_option_len;
	size_t			i;

	quote_mode = UNQUOTED;
	path_option_len = 0;
	i = 0;
	while (path_var[i])
	{
		if (!update_quote_mode_based_on_current_char(&path_var[i], &quote_mode,
				UNQUOTED) && quote_mode == UNQUOTED && path_var[i] == ':')
		{
			if (!add_path_option(&path_var[i], path_option_len,
					path_options_list))
				return (false);
			path_option_len = 0;
		}
		else
			path_option_len++;
		i++;
	}
	return (add_path_option(&path_var[i], path_option_len, path_options_list));
}

char	**get_path_options(
			char *path_var)
{
	t_list	*path_options_list;
	char	**path_options;

	path_options_list = ft_list_init();
	if (!path_options_list)
		return (NULL);
	if (!populate_path_options_list(path_var, path_options_list))
		return (ft_list_destroy(path_options_list, free), NULL);
	path_options = get_values_from_list(path_options_list);
	if (!path_options)
		return (ft_list_destroy(path_options_list, free), NULL);
	return (free(path_options_list), path_options);
}
