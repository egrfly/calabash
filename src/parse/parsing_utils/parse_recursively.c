/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_recursively.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:07:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 07:20:40 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../parse.h"
#include "../token_utils/token_utils.h"
#include "../tree_lifecycle/tree_lifecycle.h"
#include "./parsing_utils.h"

static int	process_tokens(
				t_parsing_tracker *tracker,
				t_syntax_tree *syntax_tree,
				t_multiline_options *multiline_options)
{
	t_list_node			*original_token_node;
	int					tokens_consumed_this_step_count;

	original_token_node = tracker->current_token_node;
	tokens_consumed_this_step_count
		= tracker->step.token_consumption_func(
			tracker->step.token_consumption_func_arg,
			&tracker->current_token_node, syntax_tree, multiline_options);
	if (tokens_consumed_this_step_count > 0
		&& !tracker->step.is_supported)
	{
		while (tokens_consumed_this_step_count > 0)
		{
			mark_token_as_unsupported(original_token_node->value);
			original_token_node = original_token_node->next;
			tokens_consumed_this_step_count--;
		}
		syntax_tree->contains_unsupported_features = true;
	}
	else if (tokens_consumed_this_step_count > 0
		&& tracker->current_token_node
		&& tracker->step.tree_update_func)
		tracker->step.tree_update_func(syntax_tree,
			tracker->current_token_node->prev);
	return (tokens_consumed_this_step_count);
}

static bool	unsupported_step_processed_or_mandatory_step_not_processed(
				t_parsing_tracker *tracker,
				t_syntax_tree *syntax_tree)
{
	if (tracker->tokens_consumed_this_step > 0
		&& !tracker->step.is_supported)
		deconstruct_syntax_tree_back_to_checkpoint(syntax_tree,
			BEGINNING);
	else if (tracker->tokens_consumed_this_step == 0
		&& !tracker->step.is_optional)
		deconstruct_syntax_tree_back_to_checkpoint(syntax_tree,
			tracker->checkpoint);
	else
		return (false);
	return (true);
}

static bool	advance_first_token_if_parsing_option_sequence_complete(
				t_parsing_tracker *tracker,
				const t_parsing_option_sequence_with_count *sequence,
				t_list_node **first_token_node)
{
	if (tracker->step_index == sequence->count)
	{
		*first_token_node = tracker->current_token_node;
		return (true);
	}
	return (false);
}

int	parse_recursively(
		t_list_node **first_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options,
		const t_parsing_option_sequence_with_count **sequences)
{
	t_parsing_tracker	tracker;

	tracker.checkpoint = syntax_tree->undo_actions->last;
	while (!syntax_tree->contains_unsupported_features && *sequences)
	{
		tracker.current_token_node = *first_token_node;
		tracker.tokens_consumed = 0;
		tracker.step_index = 0;
		while (tracker.step_index < (*sequences)->count)
		{
			tracker.step = (*sequences)->sequence[tracker.step_index];
			tracker.tokens_consumed_this_step
				= process_tokens(&tracker, syntax_tree, multiline_options);
			if (unsupported_step_processed_or_mandatory_step_not_processed(
					&tracker, syntax_tree))
				break ;
			tracker.tokens_consumed += tracker.tokens_consumed_this_step;
			tracker.step_index++;
		}
		if (advance_first_token_if_parsing_option_sequence_complete(
				&tracker, *sequences, first_token_node))
			return (tracker.tokens_consumed);
		sequences++;
	}
	return (0);
}
