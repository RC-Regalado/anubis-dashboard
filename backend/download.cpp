//
// Created by rc-regalado on 30/1/22.
//
#include "download.hpp"

#include <unistd.h>
#include <sys/wait.h>

#include <utility>
#include <thread>
#include <iostream>

#include <vector>

using namespace std;

#define NUM_PIPES          2

#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1

int pipes[NUM_PIPES][2];

/* always in a pipe[], pipe[0] is for read and
   pipe[1] is for write */
#define READ_FD  0
#define WRITE_FD 1

#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD]   )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )

#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD]  )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD]  )

void download::exec() {
    running = true;
    const char *bin = "/home/rc-regalado/.bin/youtube-dl";
//    const char *bin = "/bin/echo";

    // pipes for parent to write and read
    pipe(pipes[PARENT_READ_PIPE]);
    pipe(pipes[PARENT_WRITE_PIPE]);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {

        vector<const char*> params;

        params.push_back(bin);
        params.push_back(url.c_str());
        params.push_back("-f");
        params.push_back("240");

        if (!name.empty())
        {
            params.push_back("-o");
            params.push_back(name.c_str());
        }

        if (hide){
            params.push_back("-q");
        }

        params.push_back(nullptr);

        const char *args[params.size()];

        std::copy(params.begin(), params.end(), args);

        dup2(CHILD_READ_FD, STDIN_FILENO);
        dup2(CHILD_WRITE_FD, STDOUT_FILENO);

        /* Close fds not required by child. Also, we don't
           want the exec'ed program to know these existed */
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);

        execv(bin, (char **) args);

        perror("execl");
        _exit(1);
    } else {
        char buffer[100];
        ssize_t count;

        /* close fds not required by parent */
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);

        // Write to child’s stdin
        write(PARENT_WRITE_FD, "2^32\n", 5);


        while (true) {
            // Read from child’s stdout
            count = read(PARENT_READ_FD, buffer, sizeof(buffer) - 1);

            if (count == 0)
                break;

            if (count >= 0) {
                buffer[count] = 0;
                printf("Data: %s", buffer);
            } else {
                printf("IO Error\n");
            }
        }


        int code = 0;

        waitpid(pid, &code, 0);
        running = false;
    }
}


download::download(string url) : hide(false), url(std::move(url)), running(false) {}

download::download(string name, string url, bool hide) {
    this->name = std::move(name);
    this->url = std::move(url);

    this->hide = hide;

    running = true;
}

int download::run() {
    std::thread downloader(&download::exec, this);

    cout << "Thread" << endl;
    downloader.detach();

    while (running) {
        cout << "Running" << endl;
        sleep(1);
    }

    return 0;
}

string download::to_json() {
    return "{name:name}";
}

