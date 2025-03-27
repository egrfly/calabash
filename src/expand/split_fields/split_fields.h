/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_fields.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:01:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/26 16:05:28 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_FIELDS_H
# define SPLIT_FIELDS_H

# include <stdlib.h>
# include "ft_list.h"

size_t	count_split_fields(
			char *str);
t_list	*get_split_fields(
			char *str);

#endif
