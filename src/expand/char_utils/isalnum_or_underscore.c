/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalnum_or_underscore.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:08:33 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 12:09:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_ctype.h"

bool	isalnum_or_underscore(
			char c)
{
	return (ft_isalnum(c) || c == '_');
}
