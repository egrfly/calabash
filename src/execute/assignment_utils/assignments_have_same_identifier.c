/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments_have_same_identifier.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:51:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 09:55:49 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_string.h"

bool	assignments_have_same_identifier(
			char *first_assignment,
			char *second_assignment)
{
	size_t	first_assignment_length;
	size_t	second_assignment_length;

	first_assignment_length = ft_strcspn(first_assignment, "=");
	second_assignment_length = ft_strcspn(second_assignment, "=");
	return (first_assignment_length == second_assignment_length
		&& !ft_strncmp(first_assignment, second_assignment,
			first_assignment_length));
}
