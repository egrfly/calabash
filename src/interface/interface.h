/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:07:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 14:05:48 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include <stdbool.h>

# ifndef NO_ARG
#  define NO_ARG 0
# endif

# define SUCCESS 0
# define GENERAL_FAILURE 1
# define INCORRECT_USAGE 2
# define COULD_NOT_EXECUTE 126
# define NOT_FOUND 127
# define CTRL_C_TERMINATED 130
# define CTRL_BACKSLASH_TERMINATED 131

typedef struct s_multiline_options
{
	bool	input_mode_is_interactive;
	char	*(*get_next_line)(void *arg);
	void	*get_next_line_arg;
}	t_multiline_options;

int	interface(int argc, char **argv, char **envp);

#endif
