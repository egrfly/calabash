/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_operator_starts_with_chars.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:50:57 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 05:47:39 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_string.h"
#include "../lex.h"
#include "./content_utils.h"

bool	some_operator_starts_with_chars(
			char *input,
			int start_index,
			int chars_count)
{
	return (get_operator_token_content(input, start_index, chars_count));
}
