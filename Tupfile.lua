--
-- _______ __   __ __ __ __
-- |   |   |  |_|__|  |__|  |_.--.--.
-- |   |   |   _|  |  |  |   _|  |  |
-- |_______|____|__|__|__|____|___  |
--                            |_____|
--

function eval(cmd)
    local file = assert(io.popen(cmd, 'r'))
    local output = file:read('*all')
    file:close()
    return output:gsub("[\r\n]", "")
end

--
--   _______         __   __
--  |       |.-----.|  |_|__|.-----.-----.-----.
--  |   -   ||  _  ||   _|  ||  _  |     |__ --|
--  |_______||   __||____|__||_____|__|__|_____|
--           |__|
--

CXX = 'g++'
CXX_FLAGS = '-std=c++17 '
INCLUDE_FLAGS = '-I src/ -isystem lib/ '
LINK_FLAGS = ''

SRC_FILES = tup.glob("src/*.cpp")

DEBUG = true
COVERAGE = true
RELEASE = false

if not (RELEASE != DEBUG) then
    error("RELEASE and DEBUG mutually exclusive")
end

if RELEASE then
    CXX_FLAGS = CXX_FLAGS .. ' -O2'
end

if DEBUG then
    CXX_FLAGS = CXX_FLAGS .. ' -O0 -g -pg '
end

if COVERAGE then
    CXX_FLAGS = CXX_FLAGS .. '-fprofile-arcs -ftest-coverage '
    LINK_FLAGS = LINK_FLAGS .. '-lgcov --coverage '
end

--
--  _____   __ __                     __
--  |     |_|__|  |--.----.---.-.----.|__|.-----.-----.
--  |       |  |  _  |   _|  _  |   _||  ||  -__|__ --|
--  |_______|__|_____|__| |___._|__|  |__||_____|_____|
--

for _, v in ipairs({'clipp', 'linalg', 'sol3', 'spdlog', 'tinyobjloader'}) do
    INCLUDE_FLAGS = INCLUDE_FLAGS .. '-isystem ' .. 'lib/' .. v .. ' '
end

LINK_FLAGS = LINK_FLAGS .. eval('pkg-config --libs --static glfw3 lua glew gl') .. ' '

--
-- _____   __         __            ___     ______                        __ __
-- |     |_|__|.-----.|  |--.       /  /    |      |.-----.--------.-----.|__|  |.-----.
-- |       |  ||     ||    <      ,' ,'     |   ---||  _  |        |  _  ||  |  ||  -__|
-- |_______|__||__|__||__|__|    /__/       |______||_____|__|__|__|   __||__|__||_____|
--
function compile_source()
    local command = string.format(
        '%s %s -c %%f -o %%o %s',
        CXX,
        CXX_FLAGS,
        INCLUDE_FLAGS
    )

    for _, file in pairs(SRC_FILES) do
        local rule = {
            inputs = file,
            outputs = 'build/%B.o',
            command = command
        }

        if COVERAGE then
            rule.extra_outputs = { 'build/%B.gcno' }
        end

        tup.frule(rule)
    end
end

function link_source()
    local command = string.format('%s %s %%f -o %%o %s', CXX, CXX_FLAGS, LINK_FLAGS)
    tup.frule({
        inputs = tup.glob('build/*.o'),
        outputs = 'build/raytracer',
        command = command
    })
end

function compile_tests()
    for _, file in pairs(tup.glob('test/*.cpp')) do
        local rule = {
            inputs = file,
            outputs = 'build_test/%B.o',
            command = string.format('%s %s %s -c %%f -o %%o', CXX, CXX_FLAGS, INCLUDE_FLAGS),
        }

        if COVERAGE then
            rule.extra_outputs = { 'build_test/%B.gcno' }
        end

        tup.frule(rule)
    end
end

function link_tests()
    local amalgamated = {}
    tup.append_table(amalgamated, tup.glob("build/*.o"))
    tup.append_table(amalgamated, tup.glob("build_test/*.o"))
    tup.frule({
        inputs = amalgamated,
        outputs = 'build_test/test',
        command = string.format('%s %s %%f -o %%o', CXX, LINK_FLAGS)
    })
end



compile_source()
link_source()
--compile_tests()
--link_tests()
