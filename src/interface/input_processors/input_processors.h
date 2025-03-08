/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 04:18:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PROCESSORS_H
# define INPUT_PROCESSORS_H

# include "../interface.h"

int	process_noninteractive_string_input(
		char *input,
		t_program_vars *program_vars);
int	process_noninteractive_file_input(
		int fd,
		t_program_vars *program_vars);
int	process_interactive_input(
		t_program_vars *program_vars);

#endif
