/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:06:53 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 17:33:42 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stdlib.h"
#include "ft_string.h"

void	strcat_number(
			char *dest,
			int nbr)
{
	size_t	dest_len;
	size_t	nbr_len;

	dest_len = ft_strlen(dest);
	nbr_len = ft_nbrlen_base(nbr, 10);
	dest[dest_len + nbr_len] = '\0';
	while (nbr_len > 0)
	{
		dest[dest_len + nbr_len - 1] = nbr % 10 + '0';
		nbr /= 10;
		nbr_len--;
	}
}
