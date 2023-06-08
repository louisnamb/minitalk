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