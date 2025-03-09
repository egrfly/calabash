/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:45:32 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 19:36:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define NO_ARG 0
# define NO_OPTIONS 0

// Fork-related consts
# define FORK_FAILURE -1
# define CHILD_PROCESS_ID 0

// Pipe-related consts
# define PIPE_FAILURE -1
# define READ_END 0
# define WRITE_END 1
# define SINGLE_PIPE 1

// File-related consts
# define OPEN_FAILURE -1
# define DUP_FAILURE -1
# define WRITE_FAILURE -1
# define ACCESS_SUCCESS 0
# define STAT_SUCCESS 0

// Exit status codes
# define SUCCESS 0
# define GENERAL_FAILURE 1
# define INCORRECT_USAGE 2
# define COULD_NOT_EXECUTE 126
# define NOT_FOUND 127
# define SIGNAL_BASE 128

#endif
