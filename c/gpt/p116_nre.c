#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        char *argv[] = {"ls", "-la", NULL};
        execvp("ls", argv);
        perror("execvp failed");
        _exit(1);
    } else {
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid failed");
            return 1;
        }
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "ls command failed\n");
            return 1;
        }
    }

    return 0;
}