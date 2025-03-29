/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_vars_lifecycle.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:09:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/22 10:53:18 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_VARS_LIFECYCLE_H
# define PROGRAM_VARS_LIFECYCLE_H

# include <stdbool.h>
# include "../interface.h"

bool	init_program_vars(
			t_program_vars *program_vars,
			int argc,
			char **argv,
			char **envp);
void	destroy_program_vars(
			t_program_vars *program_vars);

#endif
