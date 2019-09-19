//
// filebrowserwindow.cpp
// Author: Samuel Vargas 
// Date: 09/18/2019
//

#include "filebrowserwindow.h"

FileBrowserWindow::FileBrowserWindow(const std::filesystem::path& path, const std::shared_ptr<Gui>& gui) : path(path), gui(gui) {
    reloadDirectory();
}

void FileBrowserWindow::draw() {
    ImGui::Begin("Scenes");
    if (ImGui::Button("Scan")) {
        reloadDirectory();
    }
    ImGui::Separator();

    for (const auto& p : paths) {
        ImGui::Button(p.filename().string().c_str());
    }

    ImGui::End();
}

FileBrowserWindow::~FileBrowserWindow() = default;

void FileBrowserWindow::reloadDirectory() {
    paths.clear();
    for (const auto& file : std::filesystem::directory_iterator(path)) {
        paths.emplace_back(file.path());
    }
}