#include "vcd_parser.h"
#include <sstream>
#include <iostream>

using namespace psjjjj;
using namespace std;

//cv::Mat VcdParser::parse(string vcd_code) {
string VcdParser::parse(string vcd_code) {
    istringstream iss(vcd_code);
    string code_line;
    map<string, string> mapping;
    int current_time = 0;
    map<string, vector<pair<int, int>>> wave;
    while (!iss.eof()) {
        getline(iss, code_line);
        if (code_line.empty())
            continue;
        if (code_line.at(0) == '$') {
            if (code_line.size() > 4 && string(code_line, 0, 4) == "$var") {
                istringstream issl(code_line);
                string tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
                issl >> tmp1 >> tmp2 >> tmp3 >> tmp4 >> tmp5 >> tmp6;
                if (tmp1 == "$var" && tmp6 == "$end") {
                    mapping[tmp4] = tmp5;
                    wave[tmp4] = vector<pair<int, int>>();
                }
            }
        }
        else if (code_line.at(0) == '#') {
            string time_str(code_line, 1);
            istringstream issl(time_str);
            issl >> current_time;
        }
        else if (code_line.at(0) == '0') {
            string id(code_line, 1);
            util::trim(id);
            wave[id].push_back(make_pair(current_time, 0));
        }
        else if (code_line.at(0) == '1') {
            string id(code_line, 1);
            util::trim(id);
            wave[id].push_back(make_pair(current_time, 1));
        }
    }
    
    string text = "";
    for (const auto &awave : wave) {
        string id = awave.first;
        string name = mapping[id];
        const auto &wave_info = awave.second;
        text += name + "; ";
        if (wave_info.size() == 0 || wave_info.at(0).first != 0) {
            text += "1; ";
        }
        else {
            text += wave_info.at(0).second == 0 ? "0; " : "1; ";
        }
        for (size_t i = 1; i < wave_info.size(); ++i) {
            if (wave_info.at(i).second != wave_info.at(i-1).second) {
                text += to_string(wave_info.at(i).first) + ", ";
            }
        }
        if (text.at(text.size() - 2) == ',') {
            text.at(text.size() - 2) = ';';
        }
        else {
            text += "; ";
        }
        text += "0;\n";
    }
    return text;
    
    /*
    const int kLeft = 200;
    const int kPs = 5;
    const int kTime = 100;
    const int kUpDown = 10;
    const int kA = 50;
    const int kH = kUpDown + kA + kUpDown;
    int w = kLeft + kPs * kTime;
    int h = kH * wave.size();
    cv::Mat mat = cv::Mat::zeros(h, w, CV_8UC3);
    int cnt = 0;
    for (const auto &awave : wave) {
        ++cnt;
        string id = awave.first;
        string name = mapping[id];
        const auto &wave_info = awave.second;
        int x = kLeft;
        int yH = kH * cnt - kUpDown - kA;
        int yL = yH + kA;
        int current_time = 0;
        int current_logic = 0;
	    cv::putText(mat, name, {0, yL}, CV_FONT_HERSHEY_COMPLEX, 1, {255, 255, 255});
        for (const auto &point : wave_info) {
            int new_time = point.first;
            int new_logic = point.second;
            if (new_time == 0) {
                current_time = new_time;
                current_logic = new_logic;
            }
            else {
                int y = current_logic == 1 ? yH : yL;
                cv::line(mat, {x+current_time*kPs, y}, {x+new_time*kPs, y}, {255, 255, 255});
                cv::line(mat, {x+new_time*kPs, yH}, {x+new_time*kPs, yL}, {255, 255, 255});
                current_time = new_time;
                current_logic = new_logic;
            }
        }
        if (current_time < kTime) {
            int y = current_logic == 1 ? yH : yL;
            cv::line(mat, {x+current_time*kPs, y}, {x+kTime*kPs, y}, {255, 255, 255});
        }
    }
    
    return mat;
    */
}

