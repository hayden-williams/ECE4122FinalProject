#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

// 0: tex
// 1: circle
uniform int shape_type;
uniform vec2 center;
uniform float radius;

void main()
{
    if (shape_type == 0) {
        outColor = texture(tex, Texcoord) * vec4(Color, 1.0);
        if (outColor.r > 0.95 && outColor.g > 0.95 && outColor.b > 0.95) {
            outColor.a = 0.0;
        }
    }
    else if (shape_type == 1) {
        outColor = vec4(Color, 0.0);
        float x = (gl_FragCoord.x / 800.0 - 0.5) * 2.0;
        float y = (gl_FragCoord.y / 800.0 - 0.5) * 2.0;
        if ((x - center.x) * (x - center.x) + (y - center.y) * (y - center.y) < radius * radius
            && (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y)
            > (radius - 0.01) * (radius - 0.01)) {
            outColor = vec4(0.0, 0.0, 1.0, 1.0);
        }
    }
}
