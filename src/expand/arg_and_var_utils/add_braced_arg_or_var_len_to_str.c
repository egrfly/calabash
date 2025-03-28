/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_braced_arg_or_var_len_to_str.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:55:59 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 19:50:32 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "../char_utils/char_utils.h"
#include "../escaped_string_utils/escaped_string_utils.h"

static void	print_bad_substitution_error(
				char *original_str,
				size_t i,
				size_t j)
{
	ft_dprintf(STDERR_FILENO, "%s: %.*s: bad substitution\n",
		get_program_name(),
		ft_strlen("${") + j + ft_strlen("}"),
		&original_str[i - ft_strlen("${")]);
}

size_t	add_braced_arg_or_var_len_to_str(
			char *original_str,
			int *new_str_additional_len,
			t_quote_mode quote_mode,
			t_program_vars *program_vars)
{
	size_t	i;
	size_t	j;
	char	*var_value;
	int		nbr;

	i = 1;
	j = ft_strcspn(&original_str[i], "}");
	if (isalpha_or_underscore(original_str[i])
		&& ft_strnall(&original_str[i + 1], isalnum_or_underscore, j - 1))
	{
		var_value = get_var_value_n(&original_str[i], j, program_vars->vars);
		if (var_value)
			*new_str_additional_len += strlen_with_escapes(var_value,
					quote_mode == DOUBLE_QUOTED);
	}
	else if (ft_strnall(&original_str[i], ft_isdigit, j)
		&& ft_strntoi(&original_str[i], &nbr, j) && nbr < program_vars->argc)
		*new_str_additional_len += strlen_with_escapes(program_vars->argv[nbr],
				quote_mode == DOUBLE_QUOTED);
	else
		return (print_bad_substitution_error(original_str, i, j), 0);
	*new_str_additional_len -= ft_strlen("${") + j + ft_strlen("}");
	i += j + 1;
	return (i);
}
