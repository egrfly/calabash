/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_append_both_redirection.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 15:00:13 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"

bool	perform_append_both_redirection(
			t_redirection *redirection)
{
	return (perform_write_or_append_both_redirection(redirection, O_APPEND));
}
