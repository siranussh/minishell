#include "tokenization.h"

int main(void)
{
    char test_chars[] = {'a', '=', '@', 'z', '$', '/', '!'};
    size_t i;

    for (i = 0; i < sizeof(test_chars)/sizeof(test_chars[0]); i++)
    {
        if (is_special(test_chars[i]) == -1)
            printf("'%c' is a special character.\n", test_chars[i]);
        else
            printf("'%c' is NOT a special character.\n", test_chars[i]);
    }

    return 0;
}



