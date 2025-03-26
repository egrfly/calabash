/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/26 01:18:42 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "ft_list.h"
#include "../../main.h"
#include "../execute.h"
#include "../expansions/expansions.h"

/* for debug only */
#include <readline/history.h>

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

/*	REMOVE !!! THIS WHOLE FILE / FUNCTION can be removed, once no more
 *	testing is needed
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
		add_history("echo $? \"$USER'$?'\"'$PWD' zzz '$PWD'$?ZERO!");
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
		= get_all_vars_and_values_outside_quotes(argument_node->value, program_vars, QUOTE_SINGLE);
	if (all_vars_and_values)
	{
		ft_printf("Found the below variables in above string:\n");
		print_pairs(all_vars_and_values);
		ft_printf("\n");
		result = expand_vars_to_values(argument_node->value, all_vars_and_values);
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
