/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_input_duplication.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 15:12:34 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"

bool	perform_input_duplication(
			t_redirection *redirection)
{
	return (perform_input_or_output_duplication(redirection, STDIN_FILENO));
}
