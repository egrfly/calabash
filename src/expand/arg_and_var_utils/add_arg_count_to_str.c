/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg_count_to_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:00:29 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 19:01:37 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../interface/interface.h"
#include "../escaped_string_utils/escaped_string_utils.h"

size_t	add_arg_count_to_str(
			char *new_str,
			t_program_vars *program_vars)
{
	strcat_number(new_str, program_vars->argc - 1);
	return (1);
}
