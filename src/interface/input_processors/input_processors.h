/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/24 12:29:35 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PROCESSORS_H
# define INPUT_PROCESSORS_H

# ifndef NO_ARG
#  define NO_ARG 0
# endif

int	process_noninteractive_string_input(char *input, char *program_name);
int	process_noninteractive_file_input(int fd, char *program_name);
int	process_interactive_input(char *program_name);

#endif
