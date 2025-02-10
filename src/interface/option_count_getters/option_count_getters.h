/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_count_getters.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:28:13 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:28:58 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_COUNT_GETTERS_H
# define OPTION_COUNT_GETTERS_H

int	get_c_option_count(int argc, char **argv);
int	get_options_end_count(int argc, char **argv,
		int c_option_count);

#endif
