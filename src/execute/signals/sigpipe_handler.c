/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigpipe_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:32:58 by aistok            #+#    #+#             */
/*   Updated: 2025/03/16 13:47:35 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "./signals.h"

void	sigpipe_handler(
			int signal_received,
			siginfo_t *info,
			void *ucontext)
{
	(void)signal_received;
	(void)info;
	(void)ucontext;
	g_signal = SIGPIPE;
}
