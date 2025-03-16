/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_last_exit_status.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:58:58 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/16 16:01:00 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../interface/interface.h"

int	update_last_exit_status(
		int exit_status,
		t_program_vars *program_vars)
{
	program_vars->last_exit_status = exit_status;
	return (exit_status);
}
