/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:31 by aistok            #+#    #+#             */
/*   Updated: 2025/03/06 15:11:46 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include "../../interface/interface.h"
#include "./signals.h"

int	readline_waiting_for_input_event(void)
{
	if (g_signal == SIGNAL_FOR_CTRL_C)
		rl_done = true;
	return (0);
}

void	setup_signals(void)
{
	rl_event_hook = readline_waiting_for_input_event;
	setup_signal_handler(
		SIGNAL_FOR_CTRL_C,
		ctrl_c_and_ctrl_backslash_handler, false);
	setup_signal_handler(
		SIGNAL_FOR_CTRL_BACKSLASH,
		ctrl_c_and_ctrl_backslash_handler, false);
}
