/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_get_next_line_from_file_desc        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:10:44 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/24 12:13:05 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

char	*noninteractive_get_next_line_from_file_descriptor(void *arg)
{
	return (ft_getline(*(int *)arg));
}
