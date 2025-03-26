/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:47:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/26 05:33:23 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/list_utils/list_utils.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../parse/tree_node_utils/tree_node_utils.h"
#include "../../interface/list_utils/list_utils.h"
#include "../execute.h"
#include "../builtin_utils/builtin_utils.h"
#include "../command_utils/command_utils.h"
#include "../execution_utils/execution_utils.h"
#include "../redirection_utils/redirection_utils.h"
#include "../var_utils/var_utils.h"
#include "../expansions/expansions.h"
#include "./execution_funcs.h"


#include "ft_stdio.h"

static bool	perform_assignments(
				t_list *assignments,
				t_list *vars)
{
	t_list_node	*current_assignment_node;

	current_assignment_node = assignments->first;
	while (current_assignment_node)
	{
		if (!upsert_var(current_assignment_node->value, vars,
				UNCHANGED_OR_NOT_EXPORTED))
			return (false);
		current_assignment_node = current_assignment_node->next;
	}
	return (true);
}

static void	try_execute_as_shell_script(
				char **args,
				char **envp)
{
	size_t	i;
	char	**args_with_program_name;

	i = 1;
	while (args[i - 1])
		i++;
	args_with_program_name = ft_calloc(i + 1, sizeof(char *));
	if (!args_with_program_name)
		return ;
	args_with_program_name[0] = get_program_name();
	i = 1;
	while (args[i - 1])
	{
		args_with_program_name[i] = args[i - 1];
		i++;
	}
	execve(get_program_path(), args_with_program_name, envp);
	free(args_with_program_name);
}

static int	locate_and_execute_command(
				t_binary_tree_node *node,
				t_tokens_and_syntax_tree *tokens_and_syntax_tree,
				t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_exec_params				exec_params;

	node_value = node->value;
	if (!init_exec_params(&exec_params, node_value->arguments,
			node_value->assignments, program_vars->vars))
		exit_due_to_lack_of_memory(program_vars, &exec_params,
			tokens_and_syntax_tree, node_value->redirections);
	if (!perform_redirections(node_value->redirections))
		exit_due_to_redirection_failure(program_vars, &exec_params,
			tokens_and_syntax_tree, node_value->redirections);
	if (!exec_params.path)
		exit_due_to_unfound_command(program_vars, &exec_params,
			tokens_and_syntax_tree, node_value->redirections);
	execve(exec_params.path, exec_params.args, exec_params.envp);
	if (errno == ENOEXEC)
		try_execute_as_shell_script(exec_params.args, exec_params.envp);
	exit_due_to_execve_failure(program_vars, &exec_params,
		tokens_and_syntax_tree, node_value->redirections);
	return (GENERAL_FAILURE);
}

/*
 *	In future this might be expanded to include the $IFS chars?
 */
bool	is_field_separator(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

// TODO: NORMINETTE
// TODO: LEAKS
/*
 *	This function will break the string into chunks, based on
 *	is_field_separator and will make sure, not to break quoted
 *	sequences (so, if a quoted sequence is found, ex "say hello",
 *	then, this sequence will become a chunk in it's own right,
 *	together with the quotes themselves; "..." or '...' can both
 *	happen to become chunks).
 */
t_list	*get_split_arguments(char *str, t_quote_types quote_type)
{
	t_list	*result;
	size_t	start;
	size_t	i;
	char	opening_quote;
	char	*subst;

	if (ft_strlen(str) == 0)
		return (NULL);
	// ft_printf("get_split_arguments -> str = %s\n", str);
	i = 0;
	start = 0;
	opening_quote = ' ';
	result = ft_list_init();
	while (str[i])
	{
		if (!is_quote(str[i], quote_type) && !is_quote(opening_quote, quote_type) && str[i])
		{
			if (is_field_separator(str[i]))
			{
				// ft_printf("AAA\n");
				if (i - start > 0)
				{
					subst = ft_substr(str, start, i - start);
					// ft_printf(">>%s<<\n", subst);
					ft_list_append(result, subst);
				}
				start = i + 1;
			}
		}
		else if (is_quote(str[i], quote_type) && !is_quote(opening_quote, quote_type))
		{
			// ft_printf("BBB\n");
			opening_quote = str[i];
			if (i - start > 0)
			{
				subst = ft_substr(str, start, i - start);
				// ft_printf(">>%s<<\n", subst);
				ft_list_append(result, subst);
			}
			start = i;
		}
		else if (is_quote(str[i], quote_type) && is_quote(opening_quote, quote_type) && str[i] == opening_quote)
		{
			// ft_printf("CCC\n");
			opening_quote = ' ';
			if (i - start > 0)
			{
				subst = ft_substr(str, start, i - start + 1);
				// ft_printf(">>%s<<\n", subst);
				ft_list_append(result, subst);
			}
			start = i + 1;
		}
		i++;
	}
	// ft_printf("start = %zu, i = %zu, len = %zu\n", start, i, ft_strlen(str));
	if (ft_strlen(str) > 0 && i - start > 0 && i <= ft_strlen(str))
	{
		// ft_printf("DDD\n");
		subst = ft_substr(str, start, i - start);
		// ft_printf(">>%s<<\n", subst);
		ft_list_append(result, subst);
	}
	return (result);
}


bool	has_field_separator_outside_quotes(char *str, t_quote_types quote_type)
{
	size_t	i;
	char	opened_quote;

	i = 0;
	opened_quote = ' ';
	while (str[i])
	{
		while (str[i] && !is_quote(str[i], quote_type) && !is_field_separator(str[i]))
			i++;
		if (str[i] && !is_quote(str[i], quote_type) && !is_quote(opened_quote, QUOTE_ANY) && is_field_separator(str[i]))
			return (true);
		else if (str[i] && is_quote(str[i], quote_type) && !is_quote(opened_quote, QUOTE_ANY))
			opened_quote = str[i];
		else if (str[i] && is_quote(str[i], quote_type) && is_quote(opened_quote, QUOTE_ANY) && opened_quote == str[i])
			opened_quote = ' ';
		i++;
	}
	return (false);
}

/*
 *	TODO: this function needs checking for any free-ing! LEAKS ?
 *	TODO: NORMINETTE !!
 */
t_list	*expand_arguments(
			t_list *arguments,
			t_program_vars *program_vars)
{
	t_list_node	*argument_node;
	t_list		*all_vars_and_values;
	t_list		*space_split_values;
	t_list		*new_arguments;
	char		*expanded_argument;
	char		*quotes_removed;
	char		*str_all_arguments;

	str_all_arguments = NULL;
	new_arguments = NULL;
	argument_node = arguments->first;
	space_split_values = ft_list_init();
	new_arguments = ft_list_init();
	while (argument_node)
	{
		expanded_argument = NULL;
		quotes_removed = NULL;
		all_vars_and_values = get_all_vars_and_values_outside_quotes(argument_node->value, program_vars, QUOTE_SINGLE);
		if (all_vars_and_values)
		{
			expanded_argument = expand_vars_to_values(argument_node->value, all_vars_and_values);
			if (has_field_separator_outside_quotes(expanded_argument, QUOTE_ANY))
			{
				space_split_values = get_split_arguments(expanded_argument, QUOTE_ANY);
				if (space_split_values && space_split_values->size)
				{
					t_list_node *ln = space_split_values->first;
					while (ln)
					{
						if (is_quote(((char *)ln->value)[0], QUOTE_ANY))
							ft_list_append(new_arguments, remove_quotes(ln->value));
						else
							ft_list_append(new_arguments, ln->value); //check if ft_strdup is needed ???
						ln = ln->next;
					}
				}
			}
			else
				quotes_removed = remove_quotes(expanded_argument);
		}
		else
		{
			quotes_removed = remove_quotes(argument_node->value);
		}
		if (quotes_removed)
			ft_list_append(new_arguments, quotes_removed);
		argument_node = argument_node->next;
		ft_list_destroy(all_vars_and_values, destroy_var_and_value);
		free(expanded_argument);
		//free(quotes_removed);
	}
	return (new_arguments);
}

/* TODO: REMOVE ! */
void	debug_print(char *title, t_list *list)
{
	t_list_node	*list_node;

	ft_printf("---- %s ----\n", title);
	if (!list || !list->first)
	{
		ft_printf("--> NULL\n");
		ft_printf("---- DONE ----\n");
		return ;
	}
	list_node = list->first;
	while (list_node)
	{
		ft_printf("--> %s\n", list_node->value);
		list_node = list_node->next;
	}
	ft_printf("---- DONE ----\n");
}

// TODO: heredoc ?
// TODO: NORMINETTE
// TODO: FREE node_value->arguments
int	execute_simple_command(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;

	node_value = node->value;
	if (node_value->arguments->first)
	{
		t_list	*new_arguments = expand_arguments(node_value->arguments, program_vars);
			// // ft_printf("++");
			// debug_print("ORIGINAL ARGUMENTS:", node_value->arguments); // REMOVE
			// debug_print("NEW ARGUMENTS:", new_arguments); // REMOVE
			// // TODO: !!!??? CAN WE FREE node_value->arguments HERE?!? AND REPLACE IT WITH new_arguments?
		node_value->arguments = new_arguments;
		if (node->parent && (node_is_of_type(node->parent->value, PIPE)
				|| node_is_of_type(node->parent->value, PIPE_BOTH)))
		{
			if (get_builtin(node_value->arguments->first->value))
				execute_and_exit(execute_builtin, node,
					tokens_and_syntax_tree, program_vars);
			return (locate_and_execute_command(node,
					tokens_and_syntax_tree, program_vars));
		}
		if (get_builtin(node_value->arguments->first->value))
			return (execute_builtin(node,
					tokens_and_syntax_tree, program_vars));
		return (create_child_process_and_execute(locate_and_execute_command,
				node, tokens_and_syntax_tree, program_vars));
	}
	if (!perform_redirections(node_value->redirections))
		return (GENERAL_FAILURE);
	if (!perform_assignments(node_value->assignments, program_vars->vars))
		return (revert_redirections(node_value->redirections), GENERAL_FAILURE);
	return (revert_redirections(node_value->redirections), SUCCESS);
}
