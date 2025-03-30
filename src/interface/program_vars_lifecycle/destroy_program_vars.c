/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_program_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:10:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 02:42:19 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../../execute/pipeline_lifecycle/pipeline_lifecycle.h"
#include "../../execute/redirection_utils/redirection_utils.h"
#include "../../parse/redirection_lifecycle/redirection_lifecycle.h"
#include "../interface.h"

void	destroy_program_vars(
			t_program_vars *program_vars)
{
	if (!program_vars)
		return ;
	if (program_vars->vars)
		ft_list_destroy(program_vars->vars, free);
	if (program_vars->active_pipelines)
	{
		ft_list_destroy(program_vars->active_pipelines,
			(t_action_func)destroy_pipeline);
		program_vars->active_pipelines = NULL;
	}
	if (program_vars->active_redirections)
	{
		revert_redirections(program_vars->active_redirections);
		ft_list_destroy(program_vars->active_redirections,
			(t_action_func)destroy_redirection);
		program_vars->active_redirections = NULL;
	}
}
