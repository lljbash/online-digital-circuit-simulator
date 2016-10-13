#include "simulator.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

using namespace psjjjj;
using namespace std;

SimulationResultProto Simulator::simulate(string vhdl_source_code, string output_file_path) {
    PSJJJJ_SHOW("start simulating...\n");
    SimulationResultProto srp;
    
    util::MD5 md5;
    vhdl_source_code += string("\n-- ") + std::to_string(clock());
    md5.update(vhdl_source_code);
    string md5sum = md5.toString();
    string dir = string("tmp_") + md5sum;
    
    pid_t cpid = fork();
    if (cpid < 0) {
        PSJJJJ_SHOW("Error occurred while forking!");
    }
    else if (cpid == 0) {
        mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        chdir(dir.c_str());
        
        FILE *vhdl_file = fopen("main.vhd", "w");
        fprintf(vhdl_file, "%s", vhdl_source_code.c_str());
        fclose(vhdl_file);
        
        system("vlib work");
        
        int status = system("vcom main.vhd > compile");
        if (status != 0) {
            exit(1);
        }
        
        int fd = open("log", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        dup2(fd, 2);
        close(fd);
        execlp("vsim", "vsim", "-c", "-do", "run 100ps", "main", NULL);
    }
    else {
        usleep(2000000);
        int compile_status;
        int wait_status = waitpid(cpid, &compile_status, WNOHANG);
        
        if (wait_status == 0) {
            kill(cpid, SIGKILL);
            PSJJJJ_SHOW("killed\n");
            
            system("touch output.txt");
            string cmd = string("cp ") + dir + string("/out.txt ") +
                         output_file_path + string("/") + md5sum;
            PSJJJJ_SHOW("%s\n", cmd.c_str());
            system(cmd.c_str());
#ifndef PSJJJJ_ENABLE_DEBUG
            cmd = string("rm -rf ") + dir;
            system(cmd.c_str());
#endif
            
            srp.set_success(true);
            srp.set_file_name(md5sum);
        }
        else if (compile_status != 0) {
            PSJJJJ_SHOW("Compile error!\n");
            
            string compile_path = dir + string("/compile");
            FILE *compile_file = fopen(compile_path.c_str(), "r");
            char message[1025];
            memset(message, 0, sizeof(message));
            fread(message, sizeof(char), sizeof(message), compile_file);
            string error_message = string(message);
            
            srp.set_success(false);
            srp.set_error_message(error_message);
        }
        else {
            PSJJJJ_SHOW("*****\nCRITICAL ERROR!!!!!\n*****");
            srp.set_success(false);
            srp.set_error_message("unknown error\n");
        }
        
    }
    
    PSJJJJ_SHOW("end simulating.\n");
    return srp;
}

