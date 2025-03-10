/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:10:43 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 11:59:19 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../interface.h"
#include "../list_utils/list_utils.h"
#include "./program_vars_lifecycle.h"

bool	init_program_vars(
			t_program_vars *program_vars,
			char **envp)
{
	program_vars->vars = get_list_from_values(envp);
	return (program_vars->vars);
}
