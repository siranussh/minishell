#include "tokenization.h"
int main(void)
{
    char *input;
    char *val;

    while (1)
    {
        input = readline("Enter env string (or 'exit'): ");
        if (!input)
            break;
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }

        val = extract_env_value(input);
        if (val)
            printf("Value: '%s'\n", val);
        else
            printf("No '=' found, value is NULL\n");

        free(val);
        free(input);
    }
    return 0;
}

