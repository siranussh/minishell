#include "../includes/minishell.h"

static void free_env_array(t_env_exp *e)
{
    if (!e->env)
        return;

    for (int i = 0; i < e->num_env; i++)
    {
        if (e->env[i])
        {
            free(e->env[i]);
            e->env[i] = NULL;
        }
    }
    free(e->env);
    e->env = NULL;
}

static void free_env_path(t_env_exp *e)
{
    if (e->path)
    {
        free(e->path);
        e->path = NULL;
    }
}

void free_env_exp(t_env_exp **env_exp_ptr)
{
    t_env_exp *e;

    if (!env_exp_ptr || !*env_exp_ptr)
        return;

    e = *env_exp_ptr;

    free_env_array(e);
    free_env_path(e);

    free(e);
    *env_exp_ptr = NULL;
}
