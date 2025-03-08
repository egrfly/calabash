/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:56:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 08:42:50 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./pipeline_lifecycle.h"

void	destroy_pipeline(
			t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	free(pipeline->pipe_fds);
	free(pipeline->pids);
}
