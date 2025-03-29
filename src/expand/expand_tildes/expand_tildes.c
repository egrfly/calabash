/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:32:34 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 20:13:58 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../lex/lex.h"
#include "../../parse/word_utils/word_utils.h"
#include "../../execute/var_utils/var_utils.h"
#include "../quote_mode_utils/quote_mode_utils.h"

static int	get_new_str_additional_len(
				char *var_value,
				char *home)
{
	t_quote_mode	quote_mode;
	size_t			home_len;
	int				new_str_additional_len;
	size_t			i;
	size_t			tilde_prefix_len;

	quote_mode = UNQUOTED;
	home_len = ft_strlen(home);
	new_str_additional_len = 0;
	i = 0;
	while (var_value[i])
	{
		if (!update_quote_mode_based_on_current_char(&var_value[i],
				&quote_mode, UNQUOTED) && quote_mode == UNQUOTED
			&& ((i == 0 || var_value[i - 1] == ':') && var_value[i] == '~'))
		{
			tilde_prefix_len = ft_strcspn(&var_value[i], "/:");
			if (tilde_prefix_len == 1)
				new_str_additional_len += home_len - tilde_prefix_len;
		}
		i++;
	}
	return (new_str_additional_len);
}

static void	populate_new_str(
				char *new_str,
				char *original_str,
				char *var_value,
				char *home)
{
	t_quote_mode	quote_mode;
	size_t			i;
	size_t			tilde_prefix_len;

	quote_mode = UNQUOTED;
	ft_strncat(new_str, original_str, var_value - original_str);
	i = 0;
	while (var_value[i])
	{
		if (!update_quote_mode_based_on_current_char(&var_value[i],
				&quote_mode, UNQUOTED) && quote_mode == UNQUOTED
			&& ((i == 0 || var_value[i - 1] == ':') && var_value[i] == '~'))
		{
			tilde_prefix_len = ft_strcspn(&var_value[i], "/:");
			if (tilde_prefix_len == 1)
				ft_strcat(new_str, home);
		}
		else
			ft_strncat(new_str, &var_value[i], 1);
		i++;
	}
}

static bool	expand_tildes_in_assignment(
				char **str,
				t_program_vars *program_vars)
{
	char	*home;
	char	*original_str;
	char	*var_value;
	int		new_str_additional_len;
	char	*new_str;

	home = get_var_value("HOME", program_vars->vars);
	if (!home)
		return (true);
	original_str = *str;
	var_value = &ft_strchr(original_str, '=')[1];
	new_str_additional_len = get_new_str_additional_len(var_value, home);
	new_str = ft_calloc(ft_strlen(original_str) + new_str_additional_len + 1,
			sizeof(char));
	if (!new_str)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	populate_new_str(new_str, original_str, var_value, home);
	*str = new_str;
	free(original_str);
	return (true);
}

static bool	expand_tildes_in_non_assignment(
				char **str,
				t_program_vars *program_vars)
{
	char	*home;
	size_t	tilde_prefix_len;
	char	*original_str;
	char	*new_str;

	if (**str != '~')
		return (true);
	home = get_var_value("HOME", program_vars->vars);
	tilde_prefix_len = ft_strcspn(*str, "/");
	if (!home || tilde_prefix_len > 1)
		return (true);
	original_str = *str;
	new_str = ft_strjoin(home, &original_str[1]);
	if (!new_str)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	*str = new_str;
	free(original_str);
	return (true);
}

bool	expand_tildes(
			char **str,
			t_program_vars *program_vars)
{
	char	*first_equals_sign;

	first_equals_sign = ft_strchr(*str, '=');
	if (first_equals_sign
		&& range_is_identifier(*str, 0, first_equals_sign - *str))
		return (expand_tildes_in_assignment(str, program_vars));
	else
		return (expand_tildes_in_non_assignment(str, program_vars));
}
