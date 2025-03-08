/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:10:43 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 09:20:56 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../interface.h"
#include "../list_utils/list_utils.h"
#include "./program_vars_lifecycle.h"

bool	init_program_vars(
			t_program_vars *program_vars,
			char **argv,
			char **envp)
{
	program_vars->name = argv[0];
	program_vars->env = get_list_from_values(envp);
	program_vars->local = ft_list_init();
	if (!program_vars->env || !program_vars->local)
	{
		destroy_program_vars(program_vars);
		return (false);
	}
	return (true);
}
