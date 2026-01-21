#include "Application.h"
#include "imgui/imgui.h"
#include <string>

class Logger {
    public:
        
        static Logger& GetInstance(Logger *instance){
            if (!instance) {
            instance = new Logger();
        }
        return *instance;
        }

        void LogInfo(std::string s){
            return;
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
//            logger.LogInfo("Game started successfully");
//            logger.LogGameEvent("Application initialized");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

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
