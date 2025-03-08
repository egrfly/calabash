/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_recursively.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:07:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 14:30:13 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../parse.h"
#include "../token_utils/token_utils.h"
#include "../tree_lifecycle/tree_lifecycle.h"
#include "../tree_utils/tree_utils.h"
#include "./parsing_utils.h"

static void	mark_tokens_as_unsupported(
				t_list_node *original_token_node,
				int tokens_consumed_this_step_count)
{
	while (tokens_consumed_this_step_count > 0)
	{
		mark_token_as_unsupported(original_token_node->value);
		original_token_node = original_token_node->next;
		tokens_consumed_this_step_count--;
	}
}

static int	process_tokens_according_to_parsing_option_sequence_step(
				t_parsing_tracker *tracker,
				t_syntax_tree *syntax_tree,
				t_multiline_options *multiline_options)
{
	t_list_node			*original_token_node;
	int					tokens_consumed_this_step_count;

	original_token_node = tracker->current_token_node;
	tokens_consumed_this_step_count = tracker->step.token_consumption_func(
			tracker->step.token_consumption_func_arg,
			&tracker->current_token_node, syntax_tree, multiline_options);
	if (tokens_consumed_this_step_count > 0 && !tracker->step.is_supported)
	{
		mark_tokens_as_unsupported(original_token_node,
			tokens_consumed_this_step_count);
		syntax_tree->contains_unsupported_features = true;
		return (0);
	}
	if (tokens_consumed_this_step_count > 0 && tracker->current_token_node
		&& tracker->step.tree_update_func && !tracker->step.tree_update_func(
			syntax_tree, tracker->current_token_node->prev))
	{
		if (!syntax_tree->here_doc_failure)
			syntax_tree->out_of_memory = true;
		return (0);
	}
	return (tokens_consumed_this_step_count);
}

static bool	error_encountered_or_mandatory_step_not_processed(
				t_parsing_tracker *tracker,
				t_syntax_tree *syntax_tree)
{
	if (tree_has_errors(syntax_tree))
		deconstruct_syntax_tree_back_to_checkpoint(syntax_tree,
			BEGINNING);
	else if (tracker->tokens_consumed_this_step_count == 0
		&& !tracker->step.is_optional)
		deconstruct_syntax_tree_back_to_checkpoint(syntax_tree,
			tracker->checkpoint);
	else
		return (false);
	return (true);
}

static void	process_tokens_according_to_parsing_option_sequence(
				t_syntax_tree *syntax_tree,
				t_multiline_options *multiline_options,
				const t_parsing_option_sequence_with_count *sequence,
				t_parsing_tracker *tracker)
{
	while (tracker->step_index < sequence->count)
	{
		tracker->step = sequence->sequence[tracker->step_index];
		tracker->tokens_consumed_this_step_count
			= process_tokens_according_to_parsing_option_sequence_step(
				tracker, syntax_tree, multiline_options);
		if (error_encountered_or_mandatory_step_not_processed(
				tracker, syntax_tree))
			break ;
		tracker->tokens_consumed_count
			+= tracker->tokens_consumed_this_step_count;
		tracker->step_index++;
	}
}

int	parse_recursively(
		t_list_node **first_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options,
		const t_parsing_option_sequence_with_count **sequences)
{
	t_parsing_tracker	tracker;

	tracker.checkpoint = syntax_tree->undo_actions->last;
	while (!tree_has_errors(syntax_tree) && *sequences)
	{
		tracker.current_token_node = *first_token_node;
		tracker.tokens_consumed_count = 0;
		tracker.step_index = 0;
		process_tokens_according_to_parsing_option_sequence(syntax_tree,
			multiline_options, *sequences, &tracker);
		if (tracker.step_index == (*sequences)->count)
		{
			*first_token_node = tracker.current_token_node;
			return (tracker.tokens_consumed_count);
		}
		sequences++;
	}
	return (0);
}
