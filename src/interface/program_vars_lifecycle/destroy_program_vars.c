/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_program_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:10:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 11:57:01 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "../interface.h"

void	destroy_program_vars(
			t_program_vars *program_vars)
{
	if (program_vars->vars)
		ft_list_destroy(program_vars->vars, free);
}
