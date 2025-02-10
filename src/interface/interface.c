/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:07:45 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:52:29 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stdio.h"
#include "./input_processors/input_processors.h"
#include "./option_count_getters/option_count_getters.h"
#include "./option_processors/option_processors.h"
#include "./option_utils/option_utils.h"
#include "./interface.h"

int	interface(int argc, char **argv)
{
	int	c_option_count;
	int	options_end_count;

	if (argc > 1)
	{
		c_option_count = get_c_option_count(argc, argv);
		if (option_is_unrecognised_or_unsupported(argc, argv, c_option_count))
			return (ft_dprintf(STDERR_FILENO,
					"%s: %s: unrecognised or unsupported option\n",
					argv[0], argv[1 + c_option_count]), INCORRECT_USAGE);
		options_end_count = get_options_end_count(argc, argv, c_option_count);
		if (c_option_count > 0)
			return (handle_c_option(
					argc, argv, c_option_count, options_end_count));
		if (has_more_options(argc, c_option_count, options_end_count))
			handle_external_input_file(argv, options_end_count);
	}
	if (!isatty(STDIN_FILENO))
		return (process_noninteractive_file_input(STDIN_FILENO, argv[0]));
	return (process_interactive_input(argv[0]));
}
