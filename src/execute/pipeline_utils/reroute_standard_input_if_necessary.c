/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute_standard_input_if_necessary.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:42:42 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/16 02:27:16 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../main.h"
#include "../pipeline_lifecycle/pipeline_lifecycle.h"
#include "./pipeline_utils.h"

void	reroute_standard_input_if_necessary(
			t_pipeline *pipeline)
{
	if (pipeline->current_index > 0)
		dup2(pipeline->pipe_fds[pipeline->current_index - 1][READ_END],
			STDIN_FILENO);
}
