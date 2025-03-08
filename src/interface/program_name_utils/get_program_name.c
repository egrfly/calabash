/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:46:54 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 16:04:41 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../main.h"
#include "../interface.h"

char	*access_program_name(
			t_access_mode mode,
			char *new_program_name)
{
	static char	*program_name;

	if (mode == SET)
		program_name = new_program_name;
	else if (mode == GET)
		return (program_name);
	return (NULL);
}

char	*get_program_name(void)
{
	return (access_program_name(GET, NO_ARG));
}
