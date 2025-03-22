/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_vars_and_values.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:51:21 by aistok            #+#    #+#             */
/*   Updated: 2025/03/22 17:07:59 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expansions.h"

static void	destroy_all_vars_and_values_if_empty(
				t_list **all_vars_and_values)
{
	//ft_printf("Destroying: all_vars_and_values\n");
	if (!(*all_vars_and_values)->size)
	{
		ft_list_destroy(*all_vars_and_values, destroy_var_and_value);
		*all_vars_and_values = NULL;
	}
}
t_list	*get_all_vars_and_values(
			char *str,
			t_program_vars *program_vars)
{
	t_list			*all_vars_and_values;
	size_t			i;
	size_t			var_name_len;
	char			current_quotation;

	if (!str || !str[0])
		return (NULL);
	all_vars_and_values = ft_list_init();
	i = 0;
	current_quotation = ' ';
	while (str[i])
	{
		if (is_quote(str[i], QUOTE_ANY))
		{
			if (current_quotation == ' ')
				current_quotation = str[i];
			else if (current_quotation == str[i])
				current_quotation = ' ';
		}
		var_name_len = 0;
		if (str[i] == '$' && !is_quote(current_quotation, QUOTE_SINGLE))
		{
			if (!insert_next_var_and_value(
					all_vars_and_values, str, i + 1, program_vars))
			{
				all_vars_and_values->size = 0;
				break ;
			}
			var_name_len = ((t_var_and_value *)
					all_vars_and_values->last->value)->var_name_len - 1;
		}
		i += 1 + var_name_len;
	}
	destroy_all_vars_and_values_if_empty(&all_vars_and_values);
	return (all_vars_and_values);
}
