/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history_utils.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:25:18 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 18:14:09 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HISTORY_UTILS_H
# define COMMAND_HISTORY_UTILS_H

# include <stdbool.h>

# define DO_NO_CLEANUP false
# define DO_CLEANUP true

void	command_history_update_if_suitable(
			const char *input, bool perform_cleanup);

#endif
