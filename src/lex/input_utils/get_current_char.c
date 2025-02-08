/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:54:00 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:16:39 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lex.h"

char	get_current_char(
			t_input_tracker *input_tracker)
{
	return (input_tracker->input[input_tracker->index_in_line]);
}
