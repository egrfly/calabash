/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:01:16 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 02:05:37 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_UTILS_H
# define PIPELINE_UTILS_H

# include "ft_binary_tree.h"

# define READ_END 0
# define WRITE_END 1

int		count_pipes_in_current_pipeline(
			t_binary_tree_node *node);
void	close_pipe_fds_for_process(
			int (*pipe_fds)[2],
			int pipe_count);

#endif
