/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:13:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/01 01:51:28 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PROCESSORS_H
# define INPUT_PROCESSORS_H

# include <signal.h>

# define SIGNAL_PROCESSED 100
# define SIGNAL_FOR_CTRL_C SIGINT
# define SIGNAL_FOR_CTRL_BACKSLASH SIGQUIT

# define DO_NO_CLEANUP false
# define DO_CLEANUP true

/* may need to find a better place for this? */
/* currently, declared in process_interactive_input.c */
extern volatile sig_atomic_t	global_signal;

int	process_noninteractive_string_input(
		char *input, char *program_name, char **envp);
int	process_noninteractive_file_input(
		int fd, char *program_name, char **envp);
int	process_interactive_input(
		char *program_name, char **envp);

#endif
