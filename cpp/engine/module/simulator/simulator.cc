#include "simulator.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "module/vcd_parser/vcd_parser.h"

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
        execlp("vsim", "vsim", "-c", "-do", "vcd file main.vcd;vcd add *;run 100ps;exit", "main", NULL);
    }
    else {
        int compile_status;
        int wait_status = wait(&compile_status);
        
        if (compile_status != 1) {
            string cmd = string("cp ") + dir + string("/main.vcd ") +
                         output_file_path + string("/") + md5sum;
            PSJJJJ_SHOW("%s\n", cmd.c_str());
            system(cmd.c_str());
            
            string vcd_dir = dir + "/main.vcd";
            FILE *vcd = fopen(vcd_dir.c_str(), "r");
            char code[99999];
            fread(code, 1, 99999, vcd);
            fclose(vcd);
            cv::Mat mat = VcdParser::parse(string(code));
            string png_name = md5sum + ".png";
            cv::imwrite(png_name, mat);
            cmd = string("mv ") + png_name + "../web/psjjjj/app/static";
            system(cmd.c_str());
            
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
        
#ifndef PSJJJJ_ENABLE_DEBUG
        string cmd = string("rm -rf ") + dir;
        system(cmd.c_str());
#endif
    }
    
    PSJJJJ_SHOW("end simulating.\n");
    return srp;
}

