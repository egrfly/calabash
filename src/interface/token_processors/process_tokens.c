/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:30:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:32:09 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "../../debug/debug.h"
#include "../../lex/lex.h"
#include "../interface.h"

int	process_tokens(
		t_tokens_with_status *tokens_with_status,
		t_multiline_options *multiline_options,
		char *program_name)
{
	if (!tokens_with_status)
	{
		ft_printf("%s: out of memory\n", program_name);
		return (GENERAL_FAILURE);
	}
	if (tokens_with_status->terminated_prematurely)
	{
		ft_printf("%s: a quote or bracket was not closed\n", program_name);
		return (INCORRECT_USAGE);
	}
	print_tokens(tokens_with_status->tokens);
	(void)multiline_options;
	return (0);
}
