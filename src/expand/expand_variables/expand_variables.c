/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:47:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/27 19:31:10 by emflynn          ###   ########.fr       */
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
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../lex/lex.h"
#include "../quote_mode_utils/quote_mode_utils.h"

static bool	isalnum_or_underscore(
				char c)
{
	return (ft_isalnum(c) || c == '_');
}

static size_t	strlen_with_escapes(
					char *str,
					bool is_double_quoted)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '\"'
			|| (str[i] == '\'' && !is_double_quoted))
			len++;
		len++;
		i++;
	}
	return (len);
}

static char	*strcat_with_escapes(
				char *dest,
				const char *src,
				bool is_double_quoted)
{
	size_t	i;
	size_t	j;
	size_t	quoting_char_count;

	i = 0;
	while (dest[i])
		i++;
	quoting_char_count = 0;
	j = 0;
	while (src[j])
	{
		if (src[j] == '\\' || src[j] == '\"'
			|| (src[j] == '\'' && !is_double_quoted))
		{
			dest[i + j + quoting_char_count] = '\\';
			quoting_char_count++;
		}
		dest[i + j + quoting_char_count] = src[j];
		j++;
	}
	dest[i + j + quoting_char_count] = '\0';
	return (dest);
}

bool	expand_variables(
			char **str,
			t_program_vars *program_vars,
			bool is_heredoc)
{
	char			*original_str;
	t_quote_mode	quote_mode;
	size_t			i;
	char			*new_str;
	int				new_str_additional_len;
	bool			expansion_took_place;

	original_str = *str;
	if (is_heredoc)
		quote_mode = DOUBLE_QUOTED;
	else
		quote_mode = UNQUOTED;
	new_str_additional_len = 0;
	i = 0;
	while (original_str[i])
	{
		expansion_took_place = false;
		if (!update_quote_mode_based_on_current_char(&original_str[i],
				is_heredoc, &quote_mode)
			&& (quote_mode == UNQUOTED || quote_mode == DOUBLE_QUOTED)
			&& original_str[i] == '$'
			&& original_str[i + 1])
		{
			expansion_took_place = true;
			i++;
			if (original_str[i] == '*')
			{
				// TODO: come back to this
				new_str_additional_len += ft_arrjoinlen(&program_vars->argv[1], " ") - ft_strlen("$*");
				i++;
			}
			else if (original_str[i] == '#')
			{
				new_str_additional_len += ft_nbrlen_base(program_vars->argc - 1, 10) - ft_strlen("$#");
				i++;
			}
			else if (original_str[i] == '?')
			{
				new_str_additional_len += ft_nbrlen_base(program_vars->last_exit_status, 10) - ft_strlen("$?");
				i++;
			}
			else if (ft_isdigit(original_str[i]))
			{
				if (original_str[i] - '0' < program_vars->argc)
					new_str_additional_len += strlen_with_escapes(program_vars->argv[original_str[i] - '0'], quote_mode == DOUBLE_QUOTED);
				new_str_additional_len -= 2;
				i++;
			}
			else if (ft_isalpha(original_str[i])
				|| original_str[i] == '_')
			{
				size_t	j = 0;
				while (ft_isalnum(original_str[i + j])
					|| original_str[i + j] == '_')
					j++;
				char	*var_value = get_var_value_n(&original_str[i], j, program_vars->vars);
				if (var_value)
					new_str_additional_len += strlen_with_escapes(var_value, quote_mode == DOUBLE_QUOTED);
				new_str_additional_len -= j + 1;
				i += j;
			}
			else if (original_str[i] == '{')
			{
				i++;
				size_t	j = 0;
				while (original_str[i + j] != '}')
					j++;
				if ((ft_isalpha(original_str[i]) || original_str[i] == '_')
					&& ft_strnall(&original_str[i + 1], isalnum_or_underscore, j - 1))
				{
					char	*var_value = get_var_value_n(&original_str[i], j, program_vars->vars);
					if (var_value)
						new_str_additional_len += strlen_with_escapes(var_value, quote_mode == DOUBLE_QUOTED);
				}
				else if (ft_strnall(&original_str[i], ft_isdigit, j))
				{
					int	nbr;
					if (ft_strntoi(&original_str[i], &nbr, j) && nbr < program_vars->argc)
						new_str_additional_len += strlen_with_escapes(program_vars->argv[nbr], quote_mode == DOUBLE_QUOTED);
				}
				else
					return (ft_dprintf(STDERR_FILENO, "%s: %.*s: bad substitution\n",
							get_program_name(), j + 3, &original_str[i - 2]), false);
				new_str_additional_len -= j + 3;
				i += j + 1;
			}
			else
			{
				expansion_took_place = false;
				i--;
			}
		}
		if (!expansion_took_place)
			i++;
	}
	new_str = ft_calloc(ft_strlen(original_str) + new_str_additional_len + 1, sizeof(char));
	if (!new_str)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	if (is_heredoc)
		quote_mode = DOUBLE_QUOTED;
	else
		quote_mode = UNQUOTED;
	i = 0;
	while (original_str[i])
	{
		expansion_took_place = false;
		if (!update_quote_mode_based_on_current_char(&original_str[i],
				is_heredoc, &quote_mode)
			&& (quote_mode == UNQUOTED || quote_mode == DOUBLE_QUOTED)
			&& original_str[i] == '$'
			&& original_str[i + 1])
		{
			expansion_took_place = true;
			i++;
			if (original_str[i] == '*')
			{
				// TODO: come back to this
				char	*concatenated_args = ft_arrjoin(&program_vars->argv[1], " ");
				if (!concatenated_args)
				{
					free(new_str);
					return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
							get_program_name()), false);
				}
				ft_strcat(new_str, concatenated_args);
				free(concatenated_args);
				i++;
			}
			else if (original_str[i] == '#')
			{
				char	*argc_str = ft_itostr(program_vars->argc - 1);
				if (!argc_str)
				{
					free(new_str);
					return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
							get_program_name()), false);
				}
				ft_strcat(new_str, argc_str);
				free(argc_str);
				i++;
			}
			else if (original_str[i] == '?')
			{
				char	*last_exit_status_str = ft_itostr(program_vars->last_exit_status);
				if (!last_exit_status_str)
				{
					free(new_str);
					return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
							get_program_name()), false);
				}
				ft_strcat(new_str, last_exit_status_str);
				free(last_exit_status_str);
				i++;
			}
			else if (ft_isdigit(original_str[i]))
			{
				if (original_str[i] - '0' < program_vars->argc)
					strcat_with_escapes(new_str, program_vars->argv[original_str[i] - '0'], quote_mode == DOUBLE_QUOTED);
				new_str_additional_len -= 2;
				i++;
			}
			else if (ft_isalpha(original_str[i])
				|| original_str[i] == '_')
			{
				size_t	j = 0;
				while (ft_isalnum(original_str[i + j])
					|| original_str[i + j] == '_')
					j++;
				char	*var_value = get_var_value_n(&original_str[i], j, program_vars->vars);
				if (var_value)
					strcat_with_escapes(new_str, var_value, quote_mode == DOUBLE_QUOTED);
				new_str_additional_len -= j + 1;
				i += j;
			}
			else if (original_str[i] == '{')
			{
				i++;
				size_t	j = 0;
				while (original_str[i + j] != '}')
					j++;
				if ((ft_isalpha(original_str[i]) || original_str[i] == '_')
					&& ft_strnall(&original_str[i + 1], isalnum_or_underscore, j - 1))
				{
					char	*var_value = get_var_value_n(&original_str[i], j, program_vars->vars);
					if (var_value)
						strcat_with_escapes(new_str, var_value, quote_mode == DOUBLE_QUOTED);
				}
				else if (ft_strnall(&original_str[i], ft_isdigit, j))
				{
					int	nbr;
					if (ft_strntoi(&original_str[i], &nbr, j) && nbr < program_vars->argc)
						strcat_with_escapes(new_str, program_vars->argv[nbr], quote_mode == DOUBLE_QUOTED);
				}
				new_str_additional_len -= j + 3;
				i += j + 1;
			}
			else
			{
				expansion_took_place = false;
				i--;
			}
		}
		if (!expansion_took_place)
		{
			ft_strncat(new_str, &original_str[i], 1);
			i++;
		}
	}
	*str = new_str;
	free(original_str);
	return (true);
}
