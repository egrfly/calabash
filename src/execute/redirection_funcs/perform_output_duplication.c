/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_output_duplication.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 15:13:41 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"
#include "./redirection_funcs.h"

bool	perform_output_duplication(
			t_redirection *redirection)
{
	if (redirection->right_type == REDIRECTION_RIGHT_WORD
		&& redirection->left_type == NO_REDIRECTION_LEFT_CONTENT)
		return (perform_write_both_redirection(redirection));
	return (perform_input_or_output_duplication(redirection, STDOUT_FILENO));
}
