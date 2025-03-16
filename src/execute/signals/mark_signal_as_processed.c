/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_signal_as_processed.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:50:25 by aistok            #+#    #+#             */
/*   Updated: 2025/03/15 02:25:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./signals.h"

void	mark_signal_as_processed(void)
{
	g_signal = SIGNAL_PROCESSED;
}
