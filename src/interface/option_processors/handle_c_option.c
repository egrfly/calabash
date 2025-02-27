/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:42:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/27 22:08:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stdio.h"
#include "../argument_utils/argument_utils.h"
#include "../input_processors/input_processors.h"
#include "../option_utils/option_utils.h"
#include "../interface.h"

int	handle_c_option(int argc, char **argv, char **envp, int option_count)
{
	if (!has_more_arguments(argc, option_count))
		return (ft_dprintf(STDERR_FILENO,
				"%s: -c: option requires an argument\n",
				argv[0]), INCORRECT_USAGE);
	return (process_noninteractive_string_input(
			argv[1 + option_count], argv[0], envp));
}
