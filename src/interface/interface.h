/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:07:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/22 10:51:00 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include <stdbool.h>
# include "ft_list.h"
# include "../execute/pipeline_lifecycle/pipeline_lifecycle.h"

typedef enum e_access_mode
{
	GET,
	SET,
	DELETE,
}	t_access_mode;

typedef struct s_multiline_options
{
	bool	input_mode_is_interactive;
	char	*(*get_next_line)(void *arg);
	void	*get_next_line_arg;
}	t_multiline_options;

typedef struct s_program_vars
{
	t_list		*vars;
	int			argc;
	char		**argv;
	t_pipeline	*active_pipeline;
	bool		should_exit;
	int			last_exit_status;
}	t_program_vars;

int	interface(int argc, char **argv, char **envp);

#endif
