/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_next_var_and_value.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:50:45 by aistok            #+#    #+#             */
/*   Updated: 2025/03/22 13:18:55 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "./expansions.h"
#include "../var_utils/var_utils.h"

bool	insert_next_var_and_value(
			t_list *all_vars_and_values,
			char *str,
			size_t i,
			t_program_vars *program_vars)
{
	t_var_and_value	*var_and_value;
	size_t			var_name_len;

	var_and_value = ft_calloc(1, sizeof(t_var_and_value));
	if (!var_and_value)
		return (false);
	var_name_len = get_next_var_name(str, i, &var_and_value->var_name);
	if (var_name_len)
	{
		var_and_value->var_name_len = DOLLAR_PREFIX + var_name_len;
		var_and_value->var_name_start_pos = i - DOLLAR_PREFIX;
		var_and_value->var_name_was_malloced = true;
		if (ft_strcmp(var_and_value->var_name, "?") == 0)
		{
			var_and_value->var_value = ft_itostr(program_vars->last_exit_status);
			var_and_value->var_value_was_malloced = true;
		}
		else
			var_and_value->var_value
				= get_var_value(var_and_value->var_name, program_vars->vars);
		if (var_and_value->var_value)
			var_and_value->var_value_len = ft_strlen(var_and_value->var_value);
		else
			var_and_value->var_value_len = 0;
		ft_list_append(all_vars_and_values, var_and_value);
	}
	else
		free(var_and_value);
	return (true);
}
