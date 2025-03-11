/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_property_utils.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:45:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/11 02:01:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_PROPERTY_UTILS_H
# define PROGRAM_PROPERTY_UTILS_H

# include "../interface.h"

char	*get_program_name(void);
void	set_program_name(
			char *new_program_name);
char	*get_program_path(void);
void	set_program_path(
			char *new_program_name,
			char **envp);

#endif
