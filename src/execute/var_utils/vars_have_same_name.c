/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_have_same_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:51:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 13:30:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_string.h"
#include "./var_utils.h"

bool	vars_have_same_name(
			char *first_var,
			char *second_var)
{
	size_t	first_var_length;
	size_t	second_var_length;

	if (ft_strstarts(first_var, NOT_EXPORTED_PREFIX))
		first_var++;
	if (ft_strstarts(second_var, NOT_EXPORTED_PREFIX))
		second_var++;
	first_var_length = ft_strcspn(first_var, "=");
	second_var_length = ft_strcspn(second_var, "=");
	return (first_var_length == second_var_length
		&& !ft_strncmp(first_var, second_var, first_var_length));
}
