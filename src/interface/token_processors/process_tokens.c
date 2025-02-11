/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:30:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/11 21:48:28 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG_LEXING 1
#define DEBUG_PARSING 0
#define DEBUG_EXPANSION 0

#include <unistd.h>
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
		return (ft_dprintf(STDERR_FILENO,
				"%s: out of memory\n",
				program_name), GENERAL_FAILURE);
	if (tokens_with_status->terminated_prematurely)
		return (ft_dprintf(STDERR_FILENO,
				"%s: a quote or bracket was not closed\n",
				program_name), INCORRECT_USAGE);
	if (DEBUG_LEXING)
		return (print_tokens(tokens_with_status->tokens), 0);
	(void)multiline_options;
	return (0);
}
