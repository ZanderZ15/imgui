# imgui-starter
Built on Windows


This is a logging system made from the imgui starter repository/ framework.

All modifications were made in Application.cpp, forgive me for getting lazy and not putting my classes in other files, just getting the compiler to work was a miracle.

The helper function timestamp() was adopted from Galik on stack overflow: https://stackoverflow.com/questions/24686846/get-current-time-in-milliseconds-or-hhmmssmmm-format and makes the timestamp for each log entry.

The Logger class contains various methods, the main one being Log() which does most of the heavy lifting. It logs to the cmd, the custom debug log in imgui and writes the logs to the imgui_log.txt found in /build/Debug/

The Debug log contains custom buttons to filter the info being shown by levels of severity. Enjoy