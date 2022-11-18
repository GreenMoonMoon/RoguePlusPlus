#ifndef RPP_SHADER_DATA_H
#define RPP_SHADER_DATA_H

#include "shader.h"

// language=GLSL
static const char *debugVertexSource = "#version 330 core\nlayout (location = 0) in vec2 aPos;\nlayout (location = 1) in vec2 aUV;\n\nuniform mat4 mvp;\nout vec2 uv;\nconst float aspect_ratio = 576.0/720.0;\n\nvoid main() {\n    uv = aUV;\n    gl_Position = vec4(aPos, 0.0, 1.0) * mvp;\n}";
// language=GLSL
static const char *debugFragmentSource = "#version 330 core\nin vec3 vertexColor;\nin vec2 uv;\n\nuniform sampler2D tex;\n\nout vec4 FragColor;\n\nvoid main() {\n    FragColor = texture(tex, uv);\n}";

// language=GLSL
static const char *basicVertexSource = "#version 460 core\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec3 aNor;\nlayout (location = 2) in vec2 aUV;\nlayout (location = 3) in vec4 aCol;\n\nuniform mat4 mvp;\n\nout vec3 vertexColor;\nout vec2 uv;\n\nvoid main()\n{\n    vertexColor = aCol.rgb;\n    uv = aUV;\n    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";
// language=GLSL
static const char *basicFragmentSource = "#version 460 core\nin vec3 vertexColor;\nin vec2 uv;\n\nout vec4 FragColor;\n\nvoid main()\n{\n    FragColor = vec4((vertexColor + vec3(uv, 0.0)) * 0.5f, 1.0f);\n}";

// language=GLSL
static const char *basicDiffuseVertexSource = "#version 460 core\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec3 aNor;\nlayout (location = 2) in vec2 aUV;\nlayout (location = 3) in vec4 aCol;\n\nuniform mat4 mvp;\n\nout vec3 vertexColor;\nout vec2 uv;\n\nvoid main()\n{\n    vertexColor = aCol.rgb;\n    uv = aUV;\n    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";
// language=GLSL
static const char *basicDiffuseFragmentSource = "#version 460 core\nin vec3 vertexColor;\nin vec2 uv;\n\nuniform sampler2D tex;\n\nout vec4 FragColor;\n\nvoid main()\n{\n    vec4 color = texture(tex, uv);\n    FragColor = vec4(color.rgb, 1.0f);\n}";

ShaderData ShaderData::Debug = {
    debugVertexSource,
    debugFragmentSource
};

ShaderData ShaderData::Basic = {
    basicVertexSource,
    basicFragmentSource
};

ShaderData ShaderData::BasicDiffuse = {
    basicDiffuseVertexSource,
    basicDiffuseFragmentSource
};


#endif // RPP_SHADER_DATA_H
