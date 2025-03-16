/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:10:43 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/16 15:48:20 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "../../main.h"
#include "../interface.h"
#include "../list_utils/list_utils.h"
#include "./program_vars_lifecycle.h"

bool	init_program_vars(
			t_program_vars *program_vars,
			char **envp)
{
	program_vars->vars = get_list_from_values(envp);
	program_vars->active_pipeline = NULL;
	program_vars->should_exit = false;
	program_vars->last_exit_status = SUCCESS;
	return (program_vars->vars);
}
