/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_if_opened.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:02:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 23:03:25 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define FIRST_NON_STANDARD_FD 3

void	close_if_opened(
			int fd)
{
	if (fd >= FIRST_NON_STANDARD_FD)
		close(fd);
}
