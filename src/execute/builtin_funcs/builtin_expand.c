/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/11 06:35:38 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include "ft_list.h"
#include "ft_list.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../execute.h"
#include "../execution_funcs/execution_funcs.h"
#include "../var_utils/var_utils.h"

#include <readline/history.h>


#define VAR_NAME_PREFIX 1
#define EOF_STR 1

typedef struct s_var_and_value
{
	char	*var_name;
	size_t	var_name_len;
	size_t	var_name_start_pos;
	bool	var_name_was_malloced;
	char	*var_value;
	size_t	var_value_len;
	bool	var_value_was_malloced;
}	t_var_and_value;

void	destroy_val_and_value(void *var_and_value)
{
	t_var_and_value *node_value;

	node_value = (t_var_and_value *)var_and_value;
	if (node_value->var_name_was_malloced)
	{
		free(node_value->var_name);
		node_value->var_name = NULL;
		node_value->var_name_was_malloced = false;
	}
	if (node_value->var_value_was_malloced)
	{
		free(node_value->var_value);
		node_value->var_value = NULL;
		node_value->var_value_was_malloced = false;
	}
	free(node_value);
}

int	char_allowed_for_var_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int char_allowed_for_start_of_var_name(char c)
{
	return (ft_isalpha(c) || c == '_');
}

/*
 *	If a variable name with length > 0 is found, will malloc and
 *	return A COPY for the portion from str.
 */
size_t	get_var_name(char *str, size_t position, char **var_name)
{
	size_t	var_len;
	size_t	i;

	i = position;
	if (str[i] && char_allowed_for_start_of_var_name(str[i]))
	{
		i++;
		while (str[i] && char_allowed_for_var_name(str[i]))
			i++;
	}
	var_len = i - position;
	if (var_len)
	{
		*var_name = calloc(var_len + 1, sizeof(char));
		if (!*var_name)
			*var_name = NULL;
		else
			ft_memcpy(*var_name, &str[position], var_len);
	}
	else
		*var_name = NULL;
	return (var_len);
}

t_list	*get_all_vars_and_values(char *str, t_program_vars *program_vars)
{
	t_list			*all_vars_and_values;
	t_var_and_value	*var_and_value;
	size_t			i;
	size_t			var_name_len;

	if (!str || !str[0])
		return (NULL);
	all_vars_and_values = ft_list_init();
	i = 0;
	while (str[i])
	{
		var_name_len = 0;
		if (str[i] == '$')
		{
			var_and_value = ft_calloc(1, sizeof(t_var_and_value));
			var_name_len = get_var_name(str, i + 1, &var_and_value->var_name);
			if (var_name_len)
			{
				var_and_value->var_name_len = var_name_len + VAR_NAME_PREFIX;
				var_and_value->var_name_start_pos = i;
				var_and_value->var_name_was_malloced = true;
				var_and_value->var_value
					= get_var_value(var_and_value->var_name, program_vars->vars);
				var_and_value->var_value_was_malloced = false; //this is false by calloc by default!?
				if (var_and_value->var_value)
					var_and_value->var_value_len = ft_strlen(var_and_value->var_value);
				else
					var_and_value->var_value_len = 0;
				ft_list_append(all_vars_and_values, var_and_value);
			}
			else
				free(var_and_value);
		}
		i += 1 + var_name_len;
	}
	if (!all_vars_and_values->size)
	{
		ft_list_destroy(all_vars_and_values, destroy_val_and_value);
		all_vars_and_values = NULL;
	}
	return (all_vars_and_values);
}

/* for debug only */
void	print_pairs(t_list *vars_and_values)
{
	t_list_node		*var_and_value_node;
	t_var_and_value	*var_and_value;

	if (!vars_and_values)
		return ;
	var_and_value_node = vars_and_values->first;
	while (var_and_value_node)
	{
		var_and_value = var_and_value_node->value;
		ft_printf("$%s[%d]=%s[%d]\n",
			var_and_value->var_name,
			var_and_value->var_name_len,
			var_and_value->var_value,
			var_and_value->var_value_len);
		var_and_value_node = var_and_value_node->next;
	}
}

size_t	get_new_str_length(
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

typedef enum e_string_types
{
	STR,
	NEW_STR,
}	t_string_types;

char	*replace_vars_with_values(
			char *str,
			t_list *vars_and_values)
{
	t_list_node		*var_and_value_node;
	t_var_and_value	*var_and_value;
	char			*new_str;
	size_t			start_index[2];
	size_t			chars_to_cpy;

	if (!vars_and_values)
		return (NULL);
	new_str = ft_calloc(
		get_new_str_length(str, vars_and_values), sizeof(char));
	if (!new_str)
		return (NULL);
	var_and_value_node = vars_and_values->first;
	start_index[STR] = 0;
	start_index[NEW_STR] = 0;
	while (var_and_value_node)
	{
		var_and_value = var_and_value_node->value;
		chars_to_cpy = var_and_value->var_name_start_pos - start_index[STR];
		ft_memcpy(new_str + start_index[NEW_STR], str + start_index[STR], chars_to_cpy);
		start_index[STR] += chars_to_cpy + var_and_value->var_name_len;
		start_index[NEW_STR] += chars_to_cpy;
		ft_memcpy(new_str + start_index[NEW_STR],
				var_and_value->var_value,
				var_and_value->var_value_len);
		start_index[NEW_STR] += var_and_value->var_value_len;
		var_and_value_node = var_and_value_node->next;
	}
	chars_to_cpy = ft_strlen(str) - start_index[STR];
	ft_memcpy(new_str + start_index[NEW_STR], str + start_index[STR], chars_to_cpy);
	return (new_str);
}

int	builtin_expand(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	static bool					_degub_1st_call = true;
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	t_list						*all_vals_and_values;
	char						*result;

	(void)node;
	(void)tokens_and_syntax_tree;
	
	/* for easy debug only: */
	if (_degub_1st_call)
	{
		add_history("expand \"$$asfddasfsd$USER|djafogisd$user$test\"");
		add_history("expand \"$$1asfddasfsd$USER|djafogisd$user$testuuuas2 2 32 32 $MFLAGS 222222\"");
		_degub_1st_call = false;
	}
	
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	if (!argument_node)
	{
		ft_printf("ONE argument is needed!\n");
		return (SUCCESS);
	}
	all_vals_and_values
		= get_all_vars_and_values(argument_node->value, program_vars);
	if (all_vals_and_values)
	{
		ft_printf("Found the below variables in above string:\n");
		print_pairs(all_vals_and_values);
		ft_printf("\n");
		result = replace_vars_with_values(argument_node->value, all_vals_and_values);
		ft_printf("Original [%zu]:\n"
					"%s\n"
					"Result [%zu]:\n"
					"%s\n",
					ft_strlen(argument_node->value),
					argument_node->value,
					ft_strlen(result),
					result);
		ft_list_destroy(all_vals_and_values, destroy_val_and_value);
		free(result);
	}
	else
		ft_printf("No variables found!\n");
	return (SUCCESS);
}
