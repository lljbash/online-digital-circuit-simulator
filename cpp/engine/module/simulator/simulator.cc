#include "simulator.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace psjjjj;
using namespace std;

SimulationResultProto Simulator::simulate(string vhdl_source_code) {
    PSJJJJ_SHOW("start simulating...\n");
    
    pid_t cpid = fork();
    if (cpid < 0) {
        PSJJJJ_SHOW("Error occurred while forking!");
    }
    else if (cpid == 0) {
        int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        dup2(fd, 2);
        close(fd);
        execl("/bin/echo", "echo", vhdl_source_code.c_str(), NULL);
    }
    else {
        int status;
        wait(&status);
        PSJJJJ_SHOW("return code: %d\n", status);
    }
    
    //TODO: execute modelsim to simulate
    PSJJJJ_SHOW("end simulating.\n");
    
    SimulationResultProto srp;
    srp.set_success(true);
    srp.set_file_name("example.txt");
    return srp;
}

