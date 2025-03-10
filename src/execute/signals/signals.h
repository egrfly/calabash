/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:43:31 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 22:49:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stdbool.h>

# define SIGNAL_PROCESSED -1

extern volatile sig_atomic_t	g_signal;

void	install_signal_handlers(void);
void	install_signal_handler(
			int signal_received,
			void (*signal_handler)(
				int signal_received,
				siginfo_t *info,
				void *ucontext));
void	sigint_handler(
			int signal_received,
			siginfo_t *info,
			void *ucontext);
void	sigquit_handler(
			int signal_received,
			siginfo_t *info,
			void *ucontext);
void	mark_global_signal_as_processed(void);
int		break_if_sigint_received(void);
void	toggle_terminal_echoctl_suppression(bool disable_echoctl);

#endif
