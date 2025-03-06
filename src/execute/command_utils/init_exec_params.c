/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:00:45 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 03:16:34 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "../../parse/parse.h"
#include "../list_utils/list_utils.h"
#include "../path_utils/path_utils.h"
#include "./command_utils.h"

bool	init_exec_params(
			t_exec_params *exec_params,
			t_list *arguments,
			t_list *env)
{
	exec_params->path = NULL;
	exec_params->args = get_values_from_list(arguments);
	exec_params->envp = get_values_from_list(env);
	return (exec_params->args && exec_params->envp && get_full_command_path(
			&exec_params->path, arguments->first->value,
			get_path_variable(env)));
}
