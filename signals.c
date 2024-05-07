#include "minishell.h"

void ctl_c(int a)
{
    (void)a;
    extern int g_is_in_mini;

    if (!g_is_in_mini)
    {
        rl_replace_line("", 0);
        write (1, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
    }
}
void setup_signal_handlers()
{
    rl_catch_signals = 0;
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, ctl_c);
}
