/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:50:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/26 15:51:12 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_VARIABLES_H
# define EXPAND_VARIABLES_H

# include <stdbool.h>
# include "../../interface/interface.h"

bool	expand_variables(
			char **str,
			t_program_vars *program_vars,
			bool is_heredoc);

#endif
