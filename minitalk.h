/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:40:12 by lnambaji          #+#    #+#             */
/*   Updated: 2023/06/15 15:40:17 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "printf/ft_printf.h"

struct sigaction {
    void       (*sa_handler)(int);
    sigset_t   sa_mask;
    int        sa_flags;
    void       (*sa_sigaction)(int, siginfo_t *, void *);
};

#endif
