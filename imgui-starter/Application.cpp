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

        void LogInfo(const char* s, std::vector<std::string>& logs){
            std::string logMessage = timeStamp() + " [INFO] ";
            logMessage += s;
            
            std::ofstream outputFile("imgui_log.txt", std::ios::app);

            // Check if the file was opened successfully
            if (!outputFile.is_open()) {
                std::cerr << "Error opening file!" << std::endl;
                return; // Return an error code
            }

            // Append new data to the file
            outputFile << logMessage << std::endl;
            //Print to terminal
            std::cout << logMessage << std::endl;
            //Add to imgui logs
            logs.push_back(logMessage);

            // Close the file
            outputFile.close();
        }

        void LogGameEvent(const char* s, std::vector<std::string>& logs) {
            std::string logMessage = "[GAME] ";
            logMessage += s;
            LogInfo(logMessage.c_str(), logs);
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
            static std::vector<std::string> logs;
            static Logger& logger = Logger::GetInstance(instance);

            if (first_time) {
                first_time = false;
                
                logger.LogInfo("Game started successfully", logs);
                logger.LogGameEvent("Application initialized", logs);
            }

            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

            //
            ImGui::Begin("Game Log"); 
            //
            
            if (ImGui::Button("Options")) {
                logger.LogInfo("Options", logs);
            }
            ImGui::SameLine();
            if (ImGui::Button("Clear")) {
                logger.LogInfo("Clear", logs);
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Info")) {
                logger.LogInfo("Info", logs);
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Warning")) {
                logger.LogInfo("Warning", logs);
            }   
            ImGui::SameLine();
            if (ImGui::Button("Test Error")) {
                logger.LogInfo("Error", logs);
            }

            if (ImGui::BeginChild("ChildSection1", ImVec2(650, 450), ImGuiChildFlags_Border))
                {

                    
                    
                    for (int n = 0; n < logs.size(); n++) {
                        const char* to_log = logs[n].c_str();
                        ImGui::Text(to_log);
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
