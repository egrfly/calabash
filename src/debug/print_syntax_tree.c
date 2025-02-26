/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:53:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 15:11:03 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../parse/parse.h"
#include "./debug.h"

static const
	char
	*g_node_type_descriptors[] = {
[SIMPLE_COMMAND] = "simple command",
[GROUP] = "group",
[SUBSHELL] = "subshell",
[WHILE_COMMAND] = "while",
[UNTIL_COMMAND] = "until",
[IF_COMMAND] = "if",
[FOR_COMMAND] = "for",
[SELECT_COMMAND] = "select",
[CASE_COMMAND] = "case",
[FUNCTION] = "function",
[PIPE] = "pipe",
[PIPE_BOTH] = "pipe both",
[TIME_COMMAND] = "time command",
[NEGATION] = "negation",
[OR] = "or",
[AND] = "and",
[SEQUENCE] = "sequence",
[BACKGROUND] = "background",
[COPROCESS] = "coprocess",
};

static void	print_redirection(
				t_redirection *redirection)
{
	if (redirection->left_type == REDIRECTION_LEFT_NUMBER)
		ft_printf("%d", redirection->left_content.number);
	else if (redirection->left_type == REDIRECTION_LEFT_REDIRECTION_WORD)
		ft_printf("%s", redirection->left_content.redirection_word);
	ft_printf("%s", get_operator_symbol(redirection->operator));
	if (redirection->right_type == REDIRECTION_RIGHT_DASH)
		ft_printf("-");
	else if (redirection->right_type == REDIRECTION_RIGHT_NUMBER)
		ft_printf("%d", redirection->right_content.number);
	else if (redirection->right_type == REDIRECTION_RIGHT_WORD)
		ft_printf("%s", redirection->right_content.word);
}

static void	print_values(
				char *descriptor,
				t_list *list,
				t_action_func print_node_value)
{
	t_list_node	*first_node;
	t_list_node	*current_node;

	first_node = list->first;
	ft_printf(", %s: ", descriptor);
	print_node_value(first_node->value);
	current_node = first_node->next;
	while (current_node)
	{
		ft_printf(", ");
		print_node_value(current_node->value);
		current_node = current_node->next;
	}
}

static void	print_syntax_tree_node_value(
				t_syntax_tree_node_value *value,
				int level)
{
	if (level)
		ft_printf("%*s-> ", level * 2, "");
	ft_printf("Type %s", g_node_type_descriptors[value->type]);
	if (value->assignments && value->assignments->first)
		print_values("assignments", value->assignments,
			(t_action_func)ft_putstr);
	if (value->arguments && value->arguments->first)
		print_values("arguments", value->arguments,
			(t_action_func)ft_putstr);
	if (value->redirections && value->redirections->first)
		print_values("redirections", value->redirections,
			(t_action_func)print_redirection);
	if (value->time_posix_option_set)
		ft_printf(", posix option set");
	if (value->coprocess_custom_identifier)
		ft_printf(", custom identifier: %s",
			value->coprocess_custom_identifier);
	if (value->function_identifier)
		ft_printf(", identifier: %s", value->function_identifier);
	ft_printf("\n");
}

static void	print_levels_of_syntax_tree_starting_at_node(
				t_binary_tree_node *node,
				int level)
{
	print_syntax_tree_node_value(node->value, level);
	if (node->primary_child)
		print_levels_of_syntax_tree_starting_at_node(
			node->primary_child,
			level + 1);
	if (node->secondary_child)
		print_levels_of_syntax_tree_starting_at_node(
			node->secondary_child,
			level + 1);
}

void	print_syntax_tree(
			t_binary_tree *tree)
{
	if (!tree->root)
	{
		ft_printf("(Empty tree)\n");
		return ;
	}
	print_levels_of_syntax_tree_starting_at_node(tree->root, BASE_LEVEL);
}
