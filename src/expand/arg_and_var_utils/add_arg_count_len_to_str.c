/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg_count_len_to_str.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:51:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 18:52:17 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../interface/interface.h"

size_t	add_arg_count_len_to_str(
			int *new_str_additional_len,
			t_program_vars *program_vars)
{
	*new_str_additional_len
		+= ft_nbrlen_base(program_vars->argc - 1, 10);
	*new_str_additional_len
		-= ft_strlen("$#");
	return (1);
}
