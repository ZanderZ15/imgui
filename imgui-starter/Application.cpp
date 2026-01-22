#include "Application.h"
#include "imgui/imgui.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include <utility>

std::string timeStamp() //Galik on stack overflow: https://stackoverflow.com/questions/24686846/get-current-time-in-milliseconds-or-hhmmssmmm-format
{
    using namespace std::chrono;

    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << '[' << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count() <<']';

    return oss.str();
}

class Logger {
    public:
        
        static Logger& GetInstance(Logger *instance){
            if (!instance) {
            instance = new Logger();
        }
        return *instance;
        }

        void Log(const char* s, std::vector<std::pair<std::string, int>>& logs, const int sev = 0){
            std::ofstream outputFile("imgui_log.txt", std::ios::app);
            if (!outputFile.is_open()) {
                std::cerr << "Error opening file!" << std::endl;
                return;
            }
            
            // Append new data to the file
            outputFile << s << std::endl;
            //Print to terminal
            std::cout << s << std::endl;
            //Add to imgui logs
            std::pair<std::string, int> logsy(s, sev);
            logs.push_back(logsy);
            // Close the file
            outputFile.close();
            
        }

        void INFO(const char* s, std::vector<std::pair<std::string, int>>& logs) {
            std::string logMessage = timeStamp() + " [INFO] ";
            logMessage += s;
            Log(logMessage.c_str(), logs, 0);
        }
        void WARNING(const char* s, std::vector<std::pair<std::string, int>>& logs) {
            std::string logMessage = timeStamp() + " [WARNING] ";
            logMessage += s;
            Log(logMessage.c_str(), logs, 1);
        }
        void ERROR(const char* s, std::vector<std::pair<std::string, int>>& logs) {
            std::string logMessage = timeStamp() + " [ERROR] ";
            logMessage += s;
            Log(logMessage.c_str(), logs, 2);
        }

        void LogGameEvent(const char* s, std::vector<std::pair<std::string, int>>& logs, const int sev = 0) {
            std::string logMessage = "[GAME] ";
            logMessage += s;
            if (sev == 0) {
                INFO(logMessage.c_str(), logs);
            } else if (sev == 1) {
                WARNING(logMessage.c_str(), logs);
            } else if (sev == 2) {
                ERROR(logMessage.c_str(), logs);
            }
        }
};





namespace ClassGame {
        //
        // our "global" variables
        //
        
        Logger* instance = nullptr;
        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        void GameStartUp() 
        {
            // Clear the file
            const char* filename = "imgui_log.txt";
            std::ofstream ofs(filename); 
            if (!ofs.is_open()) {
                std::cerr << "Error opening file!" << std::endl;
                return;
            }
            ofs.close(); 
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {   
            static bool first_time = true;
            //vector of logs
            static std::vector<std::pair<std::string, int>> logs;
            static Logger& logger = Logger::GetInstance(instance);

            if (first_time) {
                first_time = false;
                std::pair<std::string, int> logsy("Game started successfully", 0);
                logger.INFO("Game started successfully", logs);
                logger.LogGameEvent("Application initialized", logs);
            }

            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

            //
            ImGui::Begin("Game Control");
            //
            static bool infos = true;
            static bool warnings = true;
            static bool errors = true;
            ImGui::Text("Test Logging Buttons");
            if (ImGui::Button("Log Game Event")) {
                logger.LogGameEvent("Player made a move", logs);
            }
            ImGui::SameLine();
            if (ImGui::Button("Log Warning")) {
                logger.LogGameEvent("Invalid move attempted", logs, 1);
            }   
            ImGui::SameLine();
            if (ImGui::Button("Log Error")) {
                logger.LogGameEvent("Game state corrupted", logs, 2);
            }

            int add = 80;
            if (!infos) {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(31+add, 57+add, 88+add, 255)); //Make lighter
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(31, 57, 88, 255)); //Make darker
            }
            if (ImGui::Button("Toggle Info")) {
                if (infos) {
                    infos = false;
                } else {
                    infos = true;
                }
            }
            if (!warnings) {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(31+add, 57+add, 88+add, 255)); //Make lighter
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(31, 57, 88, 255)); //Make darker
            }
            ImGui::SameLine();
            if (ImGui::Button("Toggle Warning")) {
                if (warnings) {
                    warnings = false;
                } else {
                    warnings = true;
                }
            }
            if (!errors) {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(31+add, 57+add, 88+add, 255)); //Make lighter
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(31, 57, 88, 255)); //Make darker
            }
            ImGui::SameLine();
            if (ImGui::Button("Toggle Error")) {
                if (errors) {
                    errors = false;
                } else {
                    errors = true;
                }
            }
            ImGui::PopStyleColor(3);

            //
            ImGui::End();
            //
            
            //
            ImGui::Begin("Game Log"); 
            //
            
            if (ImGui::Button("Options")) {
                //logger.Log("Options", logs);
            }
            ImGui::SameLine();
            if (ImGui::Button("Clear")) {
                //logger.Log("Clear", logs);
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Info")) {
                logger.INFO("This is a test info message", logs);
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Warning")) {
                logger.WARNING("This is a test warning message", logs);
            }   
            ImGui::SameLine();
            if (ImGui::Button("Test Error")) {
                logger.ERROR("This is a test error message", logs);
            }

            if (ImGui::BeginChild("ChildSection1", ImVec2(650, 450), ImGuiChildFlags_Border))
                {
                    for (int n = 0; n < logs.size(); n++) {

                        if (logs[n].second == 0) {
                            if (!infos) {
                                continue;
                            }
                        } else if (logs[n].second == 1) {
                            if (!warnings) {
                                continue;
                            } 
                        } else if (logs[n].second == 2) {
                            if (!errors) {
                                continue;
                            } 
                        }

                        const char* to_log = logs[n].first.c_str();
                        if (logs[n].second == 1) { //yellow
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 218, 3, 255));
                        } 
                        else if (logs[n].second == 2) { //red
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 10, 10, 255));
                        }
                        else { //white
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
                        }
                        ImGui::Text(to_log);
                        ImGui::PopStyleColor();
                    }
                    
                }
                // 
                ImGui::EndChild();
            
            //
            ImGui::End();
            //
            
            
            
            ImGui::Begin("ImGui Log Demo");
            ImGui::LogButtons();

            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::End();
        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
        }
}
