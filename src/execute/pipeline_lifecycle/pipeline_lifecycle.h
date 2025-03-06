/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_lifecycle.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:55:30 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 17:25:16 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_LIFECYCLE_H
# define PIPELINE_LIFECYCLE_H

# define PIPE_FAILURE -1

typedef struct s_pipeline
{
	int	*pids;
	int	(*pipe_fds)[2];
	int	pipe_count;
	int	current_index;
}	t_pipeline;

int		init_pipeline(
			t_pipeline *pipeline,
			int pipe_count,
			char *program_name);
void	destroy_pipeline(
			t_pipeline *pipeline);

#endif
