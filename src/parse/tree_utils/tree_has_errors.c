/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_has_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:45:10 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 18:59:56 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../parse.h"

bool	tree_has_errors(t_syntax_tree *syntax_tree)
{
	return (syntax_tree->out_of_memory
		|| syntax_tree->contains_unsupported_features
		|| syntax_tree->input_terminated_prematurely
		|| syntax_tree->here_doc_failure);
}
