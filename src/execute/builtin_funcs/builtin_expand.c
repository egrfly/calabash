/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/21 19:39:49 by aistok           ###   ########.fr       */
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


#define DOLLAR_PREFIX 1
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

typedef enum e_string_types
{
	STR,
	NEW_STR,
}	t_string_types;

void	destroy_var_and_value(void *var_and_value)
{
	t_var_and_value *node_value;

	node_value = (t_var_and_value *)var_and_value;
	if (node_value->var_name_was_malloced)
	{
		// ft_printf("Destroying: var_name = %s\n", node_value->var_name);
		free(node_value->var_name);
		node_value->var_name = NULL;
		node_value->var_name_was_malloced = false;
	}
	if (node_value->var_value_was_malloced)
	{
		// ft_printf("Destroying: var_value = %s\n", node_value->var_value);
		free(node_value->var_value);
		node_value->var_value = NULL;
		node_value->var_value_was_malloced = false;
	}
	// ft_printf("Destroying: node\n");
	free(node_value);
}

int	char_allowed_for_var_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	char_allowed_for_start_of_var_name(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

/*
 *	If a variable name with length > 0 is found, will malloc and
 *	return A COPY for the portion from str.
 */
size_t	get_var_name(
			char *str,
			size_t position,
			char **var_name)
{
	size_t	var_len;
	size_t	i;

	i = position;
	if (str[i] && char_allowed_for_start_of_var_name(str[i]))
	{
		if (str[i] == '?' && i > 0 && str[i - 1] == '$')
			i++;
		else
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
	var_name_len = get_var_name(str, i, &var_and_value->var_name);
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

void	destroy_all_vars_and_values_if_empty(t_list **all_vars_and_values)
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
	bool			expand;

	if (!str || !str[0])
		return (NULL);
	all_vars_and_values = ft_list_init();
	i = 0;
	expand = true;
	while (str[i])
	{
		if (str[i] == '\'')
			expand = !expand;
		var_name_len = 0;
		if (str[i] == '$' && expand)
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

void	copy_var_values_into_new_str(
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

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

char	*remove_quotes(char *str)
{
	char	opening_quote;
	char	*quote_free_str;
	int		i;
	int		j;

	quote_free_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	opening_quote = ' ';
	while (str[i])
	{
		if (is_quote(str[i]) && !is_quote(opening_quote))
			opening_quote = str[i];
		else if (is_quote(opening_quote) && str[i] == opening_quote)
			opening_quote = ' ';
		else
		{
			quote_free_str[j] = str[i];
			j++;
		}
		i++;
	}
	return (quote_free_str);
}

/*
 *	TODO: $? ??? SUGGESTION: add variable with name "?" to program_vars?
 *		  and, allow a var name with one '?' ???
 */

int	builtin_expand(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	static bool					_degub_1st_call = true;
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	t_list						*all_vars_and_values;
	char						*result;
	char						*result_quote_free;

	(void)node;
	(void)tokens_and_syntax_tree;
	
	/* for easy debug only: */
	if (_degub_1st_call)
	{
		add_history("expand \"$$asfddasfsd$USER|djafogisd$user$test\"");
		add_history("expand \"$$1asfddasfsd$USER|djafogisd$user$testuuuas2 2 32 32 $MFLAGS 222222\"");
		add_history("expand $?$USER'$?$PWD\"$USER\"$USER'$?\"$USER\"$?");
		_degub_1st_call = false;
	}
	
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	if (!argument_node)
	{
		ft_printf("ONE argument is needed!\n");
		return (SUCCESS);
	}
	all_vars_and_values
		= get_all_vars_and_values(argument_node->value, program_vars);
	if (all_vars_and_values)
	{
		ft_printf("Found the below variables in above string:\n");
		print_pairs(all_vars_and_values);
		ft_printf("\n");
		result = replace_vars_with_values(argument_node->value, all_vars_and_values);
		result_quote_free = remove_quotes(result);
		ft_printf("Original [%zu]:\n"
					"%s\n"
					"Result [%zu]:\n"
					"%s\n"
					"After quote removal:\n"
					"%s\n",
					ft_strlen(argument_node->value),
					argument_node->value,
					ft_strlen(result),
					result,
					result_quote_free);
		ft_list_destroy(all_vars_and_values, destroy_var_and_value);
		free(result);
		free(result_quote_free);
	}
	else
		ft_printf("No variables found!\n");
	return (SUCCESS);
}
