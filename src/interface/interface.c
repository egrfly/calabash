/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:07:45 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/11 00:59:43 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stdio.h"
#include "../main.h"
#include "./interface.h"
#include "./input_processors/input_processors.h"
#include "./option_count_getters/option_count_getters.h"
#include "./option_processors/option_processors.h"
#include "./option_utils/option_utils.h"
#include "./program_property_utils/program_property_utils.h"

int	interface(int argc, char **argv, char **envp)
{
	int		c_option_count;
	char	*next_argument;
	int		option_count;

	set_program_name(argv[0]);
	set_program_path(argv[0], envp);
	if (argc > 1)
	{
		c_option_count = get_c_option_count(argc, argv);
		next_argument = argv[1 + c_option_count];
		if (option_is_unrecognised_or_unsupported(argc, argv, c_option_count))
			return (ft_dprintf(STDERR_FILENO,
					"%s: %s: unrecognised or unsupported option\n",
					argv[0], next_argument), INCORRECT_USAGE);
		option_count = c_option_count + get_options_end_count(argc, argv);
		next_argument = argv[1 + option_count];
		if (c_option_count > 0)
			return (handle_c_option(argv, envp, option_count));
		if (next_argument)
			return (handle_external_input_file(argv, envp, option_count));
	}
	return (handle_standard_input(envp));
}
