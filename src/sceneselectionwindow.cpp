//
// sceneselectionwindow.cpp
// Author: Samuel Vargas 
// Date: 09/18/2019
//

//
// Hardcoded Lua scenes
//

#include "sceneselectionwindow.h"

SceneSelectionWindow::SceneSelectionWindow(const std::filesystem::path& path, const std::shared_ptr<Gui>& gui) : path(path), gui(gui) {
    reloadDirectory();
}

SceneSelectionWindow::~SceneSelectionWindow() = default;

std::optional<std::filesystem::path> SceneSelectionWindow::draw() {
    ImGui::Begin("Scenes");
    if (ImGui::Button("Scan")) {
        reloadDirectory();
    }
    ImGui::Separator();

    for (const auto& p : paths) {
        if (ImGui::Button(p.filename().string().c_str())) {
            ImGui::End();
            return std::optional<std::filesystem::path>(p);
        }
    }

    ImGui::End();
    return std::nullopt;
}

void SceneSelectionWindow::reloadDirectory() {
    paths.clear();
    for (const auto& file : std::filesystem::directory_iterator(path)) {
        paths.emplace_back(file.path());
    }
}
