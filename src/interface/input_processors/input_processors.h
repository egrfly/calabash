/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 18:09:23 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PROCESSORS_H
# define INPUT_PROCESSORS_H

# include "../interface.h"

int	process_noninteractive_string_input(
		char *input,
		t_program_name_and_env *program_name_and_env);
int	process_noninteractive_file_input(
		int fd,
		t_program_name_and_env *program_name_and_env);
int	process_interactive_input(
		t_program_name_and_env *program_name_and_env);

#endif
