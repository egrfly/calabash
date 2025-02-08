/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:36:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 05:57:24 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../lex.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

bool	start_word(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	(void)multiline_options;
	return (start_token(input_tracker,
			tokens,
			create_word_token,
			has_error));
}
