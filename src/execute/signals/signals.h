/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:43:31 by aistok            #+#    #+#             */
/*   Updated: 2025/03/08 22:35:54 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stdbool.h>

# define SIGNAL_PROCESSED 100

extern volatile sig_atomic_t	g_signal;

void	setup_signals(void);
void	setup_signal_handler(
			int signal_received,
			void (*function_to_call)(),
			int block_signal_received);
void	set_global_signal_as_processed(void);
void	terminal_disable_echoctl(bool disable_ECHOCTL);
void	sigint_and_sigquit_handler(
			int signal_received, siginfo_t *info, void *ucontext);
int		readline_waiting_for_input_event(void);

#endif
