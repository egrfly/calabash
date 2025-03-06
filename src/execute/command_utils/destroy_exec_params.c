/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_exec_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:09:39 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 03:10:27 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./command_utils.h"

void	destroy_exec_params(
			t_exec_params *exec_params)
{
	free(exec_params->path);
	free(exec_params->args);
	free(exec_params->envp);
}
