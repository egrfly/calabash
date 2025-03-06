/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history_update_if_suitable.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:53:27 by aistok            #+#    #+#             */
/*   Updated: 2025/03/06 14:53:58 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <readline/history.h>
#include "ft_string.h"

/* TODO: find a better place for this function within the project structure? */
void	command_history_update_if_suitable(
			const char *input, bool perform_cleanup)
{
	static char	*last_input = NULL;

	if (perform_cleanup && last_input)
	{
		free(last_input);
		last_input = NULL;
		return ;
	}
	if (!input || (input && input[0] == '\0'))
		return ;
	if (last_input && ft_strcmp(last_input, input) == 0)
		return ;
	if (last_input)
	{
		free(last_input);
		last_input = NULL;
	}
	last_input = ft_strdup(input);
	add_history(input);
}
