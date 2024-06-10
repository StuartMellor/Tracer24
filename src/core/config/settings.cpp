#include "core/config/settings.h"

#include <fstream>
#include <iostream>
#include <string>  // Add this line to include the <string> header

Tracer::config::Settings::Settings() {
    // Check if a settings file exists
    std::ifstream SettingsFile("settings.txt");
    if (SettingsFile.is_open()) {
        loadSettings();
    };
    // Else we use default settings
}

void Tracer::config::Settings::saveSettings() {
    // Save settings to file
    std::ofstream SettingsFile("settings.txt");
    if (SettingsFile.is_open()) {
        SettingsFile << "Tracks: " << m_nTracks << std::endl;
        SettingsFile << "Steps: " << m_steps << std::endl;
        SettingsFile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

void Tracer::config::Settings::loadSettings() {
    // Load settings from file
    std::ifstream SettingsFile("settings.txt");
    if (SettingsFile.is_open()) {
        std::string line;
        while (std::getline(SettingsFile, line)) {
            if (line.find("Tracks: ") != std::string::npos) {
                m_nTracks = std::stoi(line.substr(8));
            } else if (line.find("Steps: ") != std::string::npos) {
                m_steps = std::stoi(line.substr(7));
            }
        }
        SettingsFile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

// Path: src/core/config/settings.cpp