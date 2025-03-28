/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_unbraced_env_var_to_str.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:03:12 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 19:03:39 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../execute/var_utils/var_utils.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../char_utils/char_utils.h"
#include "../escaped_string_utils/escaped_string_utils.h"

size_t	add_unbraced_env_var_to_str(
			char *original_str,
			char *new_str,
			t_quote_mode quote_mode,
			t_program_vars *program_vars)
{
	size_t	i;
	char	*var_value;

	i = 0;
	while (isalnum_or_underscore(original_str[i]))
		i++;
	var_value = get_var_value_n(original_str, i, program_vars->vars);
	if (var_value)
		strcat_with_escapes(new_str, var_value, quote_mode == DOUBLE_QUOTED);
	return (i);
}
