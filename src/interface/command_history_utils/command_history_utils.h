/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history_utils.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:25:18 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 19:59:56 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HISTORY_UTILS_H
# define COMMAND_HISTORY_UTILS_H

# include "../interface.h"

void	access_command_history(
			t_access_mode mode,
			const char *input);

#endif
