/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_funcs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:56 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 09:41:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_FUNCS_H
# define REDIRECTION_FUNCS_H

# include "../../parse/parse.h"

# define OPEN_FAILURE -1
# define DUP_FAILURE -1

typedef int	(*t_redirection_func)(
				t_redirection *redirection,
				char *program_name);

int	perform_write_redirection(
		t_redirection *redirection,
		char *program_name);

#endif
