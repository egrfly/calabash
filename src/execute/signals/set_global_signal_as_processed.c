/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_global_signal_as_processed.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:50:25 by aistok            #+#    #+#             */
/*   Updated: 2025/03/06 15:11:45 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./signals.h"

void	set_global_signal_as_processed(void)
{
	if (g_signal == SIGNAL_FOR_CTRL_C
		|| g_signal == SIGNAL_FOR_CTRL_BACKSLASH)
		g_signal = SIGNAL_PROCESSED;
}
