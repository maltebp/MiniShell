#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handleExport(const char *variable)
{
    char *name = strdup(variable);
    char *value = strchr(name, '=');

    if (value == NULL)
    {
        printf("Invalid variable format. Use NAME=VALUE.\n");
        free(name);
        return;
    }

    *value = '\0';
    value++;

    if (setenv(name, value, 1) == -1)
    {
        perror("setenv");
    }
    else
    {
        printf("Exported variable: %s=%s\n", name, value);
    }

    free(name);
}

void handleUnset(const char *variable)
{
    if (unsetenv(variable) == -1)
    {
        perror("unsetenv");
    }
    else
    {
        printf("Unset variable: %s\n", variable);
    }
}

void handleEnv()
{
    extern char **environ;
    char **env = environ;

    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}

void generateEnvFile(const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        perror("fopen");
        return;
    }

    extern char **environ;
    char **env = environ;

    while (*env != NULL)
    {
        fprintf(file, "%s\n", *env);
        env++;
    }

    fclose(file);
    printf("Generated .env file: %s\n", filename);
}