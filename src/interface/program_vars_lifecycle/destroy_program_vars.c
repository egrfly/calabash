/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_program_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:10:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 04:19:43 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "../interface.h"

void	destroy_program_vars(
			t_program_vars *program_vars)
{
	if (program_vars->env)
		ft_list_destroy(program_vars->env, free);
	if (program_vars->local)
		ft_list_destroy(program_vars->local, free);
}
