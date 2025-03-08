/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute_standard_input_if_necessary.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:42:42 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 15:58:34 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../main.h"
#include "../pipeline_lifecycle/pipeline_lifecycle.h"
#include "./pipeline_utils.h"

void	reroute_standard_input_if_necessary(
			t_pipeline *pipeline)
{
	if (pipeline->current_index < pipeline->pipe_count)
		dup2(pipeline->pipe_fds[pipeline->current_index][READ_END],
			STDIN_FILENO);
}
