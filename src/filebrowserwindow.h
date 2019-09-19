//
// filebrowserwindow.h
// Author: Samuel Vargas 
// Date: 09/18/2019
//

#pragma once
#include "gui.h"
#include <memory>
#include <filesystem>
#include <vector>
#include <string>

/**
 * TODO:
 *  - Support directories / nested files.
 *  - Filesize limits
 *  - Filter by filetype (.lua only)
 *  - …
 */

class FileBrowserWindow {
    std::shared_ptr<Gui> gui;
    std::filesystem::path path;
    std::vector<std::filesystem::path> paths;
public:
    explicit FileBrowserWindow(const std::filesystem::path& path, const std::shared_ptr<Gui>& gui);
    ~FileBrowserWindow();
    void draw();
private:
    void reloadDirectory();
};

