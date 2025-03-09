/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:26:16 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 20:35:12 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_UTILS_H
# define VARIABLE_UTILS_H

# include "ft_list.h"

char	*get_variable_value(
			t_list *variables,
			char *variable_name);

#endif
