/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:47:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 19:04:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_ctype.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../execute/var_utils/var_utils.h"
#include "../../interface/interface.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../lex/lex.h"
#include "../arg_and_var_utils/arg_and_var_utils.h"
#include "../char_utils/char_utils.h"
#include "../escaped_string_utils/escaped_string_utils.h"
#include "../quote_mode_utils/quote_mode_utils.h"

static size_t	calculate_expanded_element_len(
					char *original_str,
					int *new_str_additional_len,
					t_quote_mode quote_mode,
					t_program_vars *program_vars)
{
	if (*original_str == '*')
		return (add_positional_args_len_to_str(new_str_additional_len,
				quote_mode, program_vars));
	if (*original_str == '#')
		return (add_arg_count_len_to_str(new_str_additional_len,
				program_vars));
	if (*original_str == '?')
		return (add_last_exit_code_len_to_str(new_str_additional_len,
				program_vars));
	if (ft_isdigit(*original_str))
		return (add_single_digit_positional_arg_len_to_str(original_str,
				new_str_additional_len, quote_mode, program_vars));
	if (isalpha_or_underscore(*original_str))
		return (add_unbraced_env_var_len_to_str(original_str,
				new_str_additional_len, quote_mode, program_vars));
	if (*original_str == '{')
		return (add_braced_arg_or_var_len_to_str(original_str,
				new_str_additional_len, quote_mode, program_vars));
	return (0);
}

static bool	calculate_new_str_additional_len(
				char *original_str,
				int *new_str_additional_len,
				t_program_vars *program_vars,
				t_quote_mode base_quote_mode)
{
	t_quote_mode	quote_mode;
	size_t			i;
	bool			expansion_took_place;
	size_t			expanded_element_len;

	quote_mode = base_quote_mode;
	*new_str_additional_len = 0;
	i = 0;
	while (original_str[i])
	{
		expansion_took_place = false;
		if (should_expand(&original_str[i], &quote_mode, base_quote_mode))
		{
			expanded_element_len = calculate_expanded_element_len(
					&original_str[i + 1], new_str_additional_len,
					quote_mode, program_vars);
			if (!expanded_element_len)
				return (false);
			i += expanded_element_len + 1;
			expansion_took_place = true;
		}
		if (!expansion_took_place)
			i++;
	}
	return (true);
}

static size_t	add_expanded_element(
					char *original_str,
					char *new_str,
					t_quote_mode quote_mode,
					t_program_vars *program_vars)
{
	if (*original_str == '*')
		return (add_positional_args_to_str(new_str, quote_mode, program_vars));
	if (*original_str == '#')
		return (add_arg_count_to_str(new_str, program_vars));
	if (*original_str == '?')
		return (add_last_exit_code_to_str(new_str, program_vars));
	if (ft_isdigit(*original_str))
		return (add_single_digit_positional_arg_to_str(original_str, new_str,
				quote_mode, program_vars));
	if (isalpha_or_underscore(*original_str))
		return (add_unbraced_env_var_to_str(original_str, new_str, quote_mode,
				program_vars));
	if (*original_str == '{')
		return (add_braced_arg_or_var_to_str(original_str, new_str, quote_mode,
				program_vars));
	return (0);
}

static void	populate_new_str(
				char *original_str,
				char *new_str,
				t_program_vars *program_vars,
				t_quote_mode base_quote_mode)
{
	t_quote_mode	quote_mode;
	size_t			i;
	bool			expansion_took_place;

	quote_mode = base_quote_mode;
	i = 0;
	while (original_str[i])
	{
		expansion_took_place = false;
		if (should_expand(&original_str[i], &quote_mode, base_quote_mode))
		{
			i += add_expanded_element(&original_str[i + 1], new_str,
					quote_mode, program_vars) + 1;
			expansion_took_place = true;
		}
		if (!expansion_took_place)
			ft_strncat(new_str, &original_str[i++], 1);
	}
}

bool	expand_variables(
			char **str,
			t_program_vars *program_vars,
			bool is_heredoc)
{
	t_quote_mode	base_quote_mode;
	char			*original_str;
	char			*new_str;
	int				new_str_additional_len;

	base_quote_mode = UNQUOTED;
	if (is_heredoc)
		base_quote_mode = DOUBLE_QUOTED;
	original_str = *str;
	if (!calculate_new_str_additional_len(original_str, &new_str_additional_len,
			program_vars, base_quote_mode))
		return (false);
	new_str = ft_calloc(ft_strlen(original_str) + new_str_additional_len + 1,
			sizeof(char));
	if (!new_str)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	populate_new_str(original_str, new_str, program_vars, base_quote_mode);
	*str = new_str;
	free(original_str);
	return (true);
}
