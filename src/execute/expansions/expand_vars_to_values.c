/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_to_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:53:45 by aistok            #+#    #+#             */
/*   Updated: 2025/03/22 16:45:31 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdlib.h"
#include "ft_ctype.h"
#include "./expansions.h"

static size_t	get_new_str_length(
			char	*str,
			t_list 	*vars_and_values)
{
	t_list_node		*var_and_value_node;
	t_var_and_value	*var_and_value;
	size_t			total_var_names_len;
	size_t 			total_var_values_len;

	if (!vars_and_values)
		return (0);
	total_var_names_len = 0;
	total_var_values_len = 0;
	var_and_value_node = vars_and_values->first;
	while (var_and_value_node)
	{
		var_and_value = var_and_value_node->value;
		total_var_names_len += var_and_value->var_name_len;
		total_var_values_len += var_and_value->var_value_len;
		var_and_value_node = var_and_value_node->next;
	}
	return (ft_strlen(str) - total_var_names_len
		+ total_var_values_len + EOF_STR);
}

static void	copy_var_values_into_new_str(
			char *new_str,
			char *str,
			size_t start_index[2],
			t_var_and_value *var_and_value)
{
	size_t	chars_to_cpy;

	chars_to_cpy = var_and_value->var_name_start_pos - start_index[STR];
	ft_memcpy(new_str + start_index[NEW_STR],
			str + start_index[STR], chars_to_cpy);
	start_index[STR] += chars_to_cpy + var_and_value->var_name_len;
	start_index[NEW_STR] += chars_to_cpy;
	ft_memcpy(new_str + start_index[NEW_STR],
			var_and_value->var_value,
			var_and_value->var_value_len);
	start_index[NEW_STR] += var_and_value->var_value_len;
}

/*
 *	expand_vars_to_values will replace all variables present in the
 *	vars_and_values linked list with the associated values and return
 *	a NEW STRING (via ft_calloc)
 *
 * 	if vars_and_values == NULL, then a duplicate of the string str is
 *	returned (via ft_strdup)
 *
 * 	NULL is returned ONLY when there is not enough memory to perform
 * 	the variable expansion!
 */
char	*expand_vars_to_values(
			char *str,
			t_list *vars_and_values)
{
	t_list_node		*var_and_value_node;
	t_var_and_value	*var_and_value;
	char			*new_str;
	size_t			start_index[2];
	size_t			chars_to_cpy;

	if (!vars_and_values)
		return (ft_strdup(str));
	new_str = ft_calloc(
		get_new_str_length(str, vars_and_values), sizeof(char));
	if (!new_str)
		return (NULL);
	start_index[STR] = 0;
	start_index[NEW_STR] = 0;
	var_and_value_node = vars_and_values->first;
	while (var_and_value_node)
	{
		var_and_value = var_and_value_node->value;
		copy_var_values_into_new_str(new_str, str, start_index, var_and_value);
		var_and_value_node = var_and_value_node->next;
	}
	chars_to_cpy = ft_strlen(str) - start_index[STR];
	ft_memcpy(new_str + start_index[NEW_STR],
		str + start_index[STR], chars_to_cpy);
	return (new_str);
}
