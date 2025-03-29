/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quoting.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:54:40 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/26 16:00:42 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMOVE_QUOTING_H
# define REMOVE_QUOTING_H

# include <stdbool.h>

bool	remove_quoting(
			char *str,
			bool is_heredoc);

#endif
