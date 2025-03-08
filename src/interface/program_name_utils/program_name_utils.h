/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_name_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:45:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 12:51:41 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_NAME_UTILS_H
# define PROGRAM_NAME_UTILS_H

# include "../interface.h"

char	*get_program_name(void);
char	*access_program_name(
			t_access_mode mode,
			char *new_program_name);

#endif
