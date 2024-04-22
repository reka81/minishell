#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // printf("ss\n");
    look_for_path("ls", getenv("PATH"));
}