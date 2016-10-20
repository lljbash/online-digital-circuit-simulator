#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <gflags/gflags.h>
#include "engine.h"
#include "request.pb.h"

using namespace psjjjj;
using namespace std;

DEFINE_int32(port, 1234, "Socket listen port");
DEFINE_string(out, "tmp", "Result file path");
DEFINE_string(module_path, "data/vhdl", "Chip module path");
DEFINE_string(module_list, "chip_list.txt", "Chip module list file name");

void handle_request(int clnt_sock) {
    char request_str[255555] = "";
    read(clnt_sock, request_str, sizeof(request_str) - 1);
    RequestProto request;
    request.ParseFromString(string(request_str));
    
    string result;
    EnginePtr engine = Engine::createEngine(FLAGS_out);
    engine->addChipModules(FLAGS_module_path, FLAGS_module_list);
    switch (request.type()) {
        case 0:
            result = engine->getCircuitParsingResult(request.circuit().SerializeAsString());
            break;
        case 1:
            result = engine->getSimulationResult(request.vhdl_code());
            break;
        case 2:
            result = engine->getChipModuleList();
            break;
        default:
            result = "";
    }   
    write(clnt_sock, result.c_str(), result.length());
    close(clnt_sock);
}

int main(int argc, char *argv[]) {
    ::google::ParseCommandLineFlags(&argc, &argv, true);
    cout << "port: " << FLAGS_port << endl;
    
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(FLAGS_port);
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(serv_sock, 30);
    while (true) {
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        std::thread t(handle_request, clnt_sock);
        t.detach();
    }
    close(serv_sock);
    return 0;
}

