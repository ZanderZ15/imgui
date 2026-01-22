# imgui-starter
Built on Windows


This is a logging system made from the imgui starter repository/ framework.

All modifications were made in Application.cpp, forgive me for getting lazy and not putting my classes in other files, just getting the compiler to work was a miracle.

The helper function timestamp() was adopted from Galik on stack overflow: https://stackoverflow.com/questions/24686846/get-current-time-in-milliseconds-or-hhmmssmmm-format and makes the timestamp for each log entry.

The Logger class contains various methods, the main one being Log() which does most of the heavy lifting. It logs to the cmd, the custom debug log in imgui and writes the logs to the imgui_log.txt found in /build/Debug/

The Debug log contains custom buttons to filter the info being shown by levels of severity. 



Getting Cmake to work was the biggest hurdle. After that I had to look up all of the possible things that imgui offers.

The buttons and text were faily straightforward but I spent a few minutes figuring out how to initialize variables on the first go (thank you static variables). I also nearly had an anurism when I realized that the way text was being made in the debug didnt save the color and I had to redo most of my functions to create a vector of pairs, the pairs containing the text and an int corresponding to a color.

I also decided to cut the functionality of clear and option and the command bar entirely in favor of time, especially since the main goal of this assignment is to create a logging system that logs though I did think about how I would implement those.

Overall, the screenshot of the desired end-goal was very helpful in reverse engineering the debug log and I didn't need to ask for clarification for any part of the assignment.



Enjoy!