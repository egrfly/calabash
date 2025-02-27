/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_processors.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:44:09 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 20:11:08 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_PROCESSORS_H
# define OPTION_PROCESSORS_H

int	handle_c_option(int argc, char **argv, char **envp,
		int option_count);
int	handle_external_input_file(char **argv, char **envp,
		int options_end_count);

#endif
