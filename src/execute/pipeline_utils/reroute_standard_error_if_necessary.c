/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute_standard_error_if_necessary.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:42:42 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 09:20:26 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../main.h"
#include "../pipeline_lifecycle/pipeline_lifecycle.h"
#include "./pipeline_utils.h"

void	reroute_standard_error_if_necessary(
			t_pipeline *pipeline)
{
	if (pipeline->current_index > 0)
		dup2(pipeline->pipe_fds[pipeline->current_index - 1][WRITE_END],
			STDERR_FILENO);
}
