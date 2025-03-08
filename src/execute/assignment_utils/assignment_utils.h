/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:49:43 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 09:53:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSIGNMENT_UTILS_H
# define ASSIGNMENT_UTILS_H

# include <stdbool.h>
# include "ft_list.h"

bool	assignments_have_same_identifier(
			char *first_assignment,
			char *second_assignment);
void	filter_out_duplicate_assignments(
			t_list *env);

#endif
