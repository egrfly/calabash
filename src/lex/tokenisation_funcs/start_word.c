/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:36:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 05:10:06 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../interface/interface.h"
#include "../lex.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

bool	start_word(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	(void)multiline_options;
	return (start_token(input_tracker,
			tokens_with_status,
			create_word_token));
}
