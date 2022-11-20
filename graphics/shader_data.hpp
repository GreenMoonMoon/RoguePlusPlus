#ifndef RPP_SHADER_DATA_HPP
#define RPP_SHADER_DATA_HPP

#include <fstream>
#include <filesystem>

static std::string readShaderFile(const std::filesystem::path &filePath) {
    constexpr auto readSize = size_t(4096);
    auto stream = std::ifstream(filePath);
    stream.exceptions(std::ios_base::badbit);

    auto out = std::string();
    auto buffer = std::string(readSize, '\0');
    while(stream.read(&buffer[0], readSize)) {
        out.append(buffer, 0, stream.gcount());
    }
    out.append(buffer, 0, stream.gcount());
    return std::move(out);
}

struct ShaderData {
    std::string vertexSource;
    std::string fragmentSource;

    // TODO: check for potential memory leak...
    void LoadFromFiles(const std::string &vertexFile, const std::string &fragmentFile) {
        vertexSource = readShaderFile(vertexFile);
        fragmentSource = readShaderFile(fragmentFile);
    }
};

#endif // RPP_SHADER_DATA_HPP
