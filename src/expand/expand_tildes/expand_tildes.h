/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:50:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/26 15:46:24 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_TILDES_H
# define EXPAND_TILDES_H

# include <stdbool.h>
# include "../../interface/interface.h"

bool	expand_tildes(
			char **str,
			t_program_vars *program_vars);

#endif
