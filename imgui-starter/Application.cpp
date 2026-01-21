#include "Application.h"
#include "imgui/imgui.h"
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>

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

        void LogInfo(const char* s){
            std::string logMessage = timeStamp() + " [INFO] ";
            logMessage += s;
            ImGui::LogText(logMessage.c_str());
            std::cout << logMessage << std::endl;
        }

        void LogGameEvent(const char* s) {
            std::string logMessage = "[GAME] ";
            logMessage += s;
            LogInfo(logMessage.c_str());
        }
};





namespace ClassGame {
        //
        // our global variables
        //
        
        Logger* instance = nullptr;
        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        void GameStartUp() 
        {
            // Initialize logging system
            Logger& logger = Logger::GetInstance(instance);
            logger.LogInfo("Game started successfully");
            logger.LogGameEvent("Application initialized");
            

        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
            Logger& logger = Logger::GetInstance(instance);
            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

            ImGui::Begin("Game Log"); 

            
            if (ImGui::Button("Options")) {
                logger.LogInfo("Options");
            }
            ImGui::SameLine();
            if (ImGui::Button("Clear")) {
                logger.LogInfo("Clear");
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Info")) {
                logger.LogInfo("Info");
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Warning")) {
                logger.LogInfo("Warning");
            }   
            ImGui::SameLine();
            if (ImGui::Button("Test Error")) {
                logger.LogInfo("Error");
            }
            

            ImGui::End();

            
            
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
