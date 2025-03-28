/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expandable_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:43:03 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 18:51:03 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_ctype.h"
#include "ft_string.h"

bool	is_expandable_char(
			char c)
{
	return (c && (ft_isalnum(c) || ft_strchr("*#?_{", c)));
}
