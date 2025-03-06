/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:07:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 18:33:20 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include <stdbool.h>
# include "ft_list.h"

# ifndef NO_ARG
#  define NO_ARG 0
# endif

# define SUCCESS 0
# define GENERAL_FAILURE 1
# define INCORRECT_USAGE 2
# define COULD_NOT_EXECUTE 126
# define NOT_FOUND 127

typedef struct s_multiline_options
{
	bool	input_mode_is_interactive;
	char	*(*get_next_line)(void *arg);
	void	*get_next_line_arg;
}	t_multiline_options;

typedef struct s_program_name_and_env
{
	char	*name;
	t_list	*env;
}	t_program_name_and_env;

int	interface(int argc, char **argv, char **envp);

#endif
