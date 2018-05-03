#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

// 0: tex
// 1: circle
// 2: line
uniform int shape_type;
uniform vec2 center; // for circle
uniform float radius; // for circle
uniform vec2 start; // for line
uniform vec2 end; // for line
uniform float distance; // for line

// screen size
uniform int width;
uniform int height;

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

        vec3 changed_coord = gl_FragCoord.xyz / gl_FragCoord.w;
        float x = (changed_coord.x / (width) - 0.5) * 2.0;
        float y = (changed_coord.y / (height) - 0.5) * 2.0;

        if ((x - center.x) * (x - center.x) + (y - center.y) * (y - center.y) < radius * radius
            && (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y)
            > (radius - 0.01) * (radius - 0.01)) {
            outColor = vec4(0.0, 0.0, 1.0, 1.0);
        }
    }
    else if (shape_type == 2) {
        outColor = vec4(Color, 0.0);

        vec3 changed_coord = gl_FragCoord.xyz / gl_FragCoord.w;
        float x = (changed_coord.x / (width) - 0.5) * 2.0;
        float y = (changed_coord.y / (height) - 0.5) * 2.0;

        float dxc = x - start.x;
        float dyc = y - start.y;

        float dxl = end.x - start.x;
        float dyl = end.y - start.y;

        float cross = dxc * dyl - dyc * dxl;

        float orig_distance = sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
        float vx = end.x - start.x;
        float vy = end.y - start.y;
        float mag = sqrt(vx * vx + vy * vy);
        float ux = vx / mag;
        float uy = vy / mag;
        //float dist = percent * orig_distance;
        float dist = distance;
        float endx = start.x + dist * ux;
        float endy = start.y + dist * uy;

        if (abs(cross) > 0.01 * orig_distance) {
            return;
        }

        if (abs(dxl) >= abs(dyl)) {
            if (dxl > 0) {
                if (start.x <= x && x <= endx) {
                    outColor = vec4(0.0, 0.0, 0.0, 1.0);
                    return;
                }
            } else {
                if (endx <= x && x <= start.x) {
                    outColor = vec4(0.0, 0.0, 0.0, 1.0);
                    return;
                }
            }
        } else {
            if (dyl > 0) {
                if (start.y <= y && y <= endy) {
                    outColor = vec4(0.0, 0.0, 0.0, 1.0);
                    return;
                }
            } else {
                if (endy <= y && y <= start.y) {
                    outColor = vec4(0.0, 0.0, 0.0, 1.0);
                    return;
                }
            }
        }

    }
}
