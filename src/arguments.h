//
// arguments.h
// Author: Samuel Vargas
// Date: 09/15/2019
//

#include "tinydir.h" // TODO: Remove tinydir, pretty sure <filesystem> does everything now
#include <optional>
#include <filesystem>

class Arguments {
public:
    std::optional<std::filesystem::path> scriptDirectory;
private:
    explicit Arguments();
    explicit Arguments(const std::filesystem::path& scriptDirectory);
public:
    static Arguments handleArguments(int ac, char** av);
};
