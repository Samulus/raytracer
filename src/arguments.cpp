//
// arguments.cpp
// Author: Samuel Vargas 
// Date: 09/15/2019
//

#include "clipp.h"
#include "arguments.h"
#include "version.h"
#include <iostream>
#include <filesystem>
#include <spdlog/spdlog.h>

Arguments::Arguments() : scriptDirectory(std::nullopt) {
}

Arguments::Arguments(const std::filesystem::path& scriptDirectory) :
    scriptDirectory(std::optional<std::filesystem::path>(scriptDirectory)) {
}

Arguments Arguments::handleArguments(int ac, char** av) {
    std::string scriptDirectory;
    bool version = false;

    const auto cli = (
            clipp::value("script-directory")
                   .doc("Path to directory containing lua scene paths.")
                   .required(false)
                   .set(scriptDirectory),

            clipp::option("-v")
                   .doc("Display program version")
                   .required(false)
                   .set(version)
    );

    const std::string programName = std::filesystem::path(av[0]).filename();

    const auto result = clipp::parse(ac, av, cli);
    if (!result) {
        std::cout << clipp::make_man_page(cli, programName);
        std::exit(1);
    }

    if (version) {
        std::cout << VERSION << std::endl;
        std::exit(0);
    }

    if (scriptDirectory.empty()) {
        spdlog::info("'{}' set as lua scene directory.", scriptDirectory);
        return Arguments();
    }

    return Arguments(std::filesystem::path(scriptDirectory));
}
