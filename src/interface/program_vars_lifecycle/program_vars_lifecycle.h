/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_vars_lifecycle.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:09:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 12:54:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_VARS_LIFECYCLE_H
# define PROGRAM_VARS_LIFECYCLE_H

# include <stdbool.h>
# include "../interface.h"

bool	init_program_vars(
			t_program_vars *program_vars,
			char **envp);
void	destroy_program_vars(
			t_program_vars *program_vars);

#endif
