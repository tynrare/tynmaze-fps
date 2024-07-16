#version 100

precision mediump float;

varying vec3 fragPosition;
varying vec2 fragTexCoord;
varying vec4 fragColor;
varying vec3 fragNormal;
varying mat3 TBN;

uniform sampler2D texture0;
uniform sampler2D tex_noise0;

float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

float rand(vec3 co) {
    return fract(sin(dot(co.xyz, vec3(12.9898, 78.233, 138.1203))) * 43758.5453);
}

void main()
{
    bool top = fragNormal.y < 0.0;
    bool bottom = fragNormal.y > 0.0;
    bool side_a = fragNormal.x > 0.0 || fragNormal.z > 0.0;
    bool side_b = fragNormal.x < 0.0 || fragNormal.z < 0.0;

    vec2 uv = fragTexCoord;
    uv *= 0.25;
    if (top) {
        uv.y -= 0.25; // discard to zero
    } else if(bottom) {
        uv -= 0.25; // discard to zero
        uv.y += 0.5;
    } else if(side_b || side_a) {
        if (side_b) {
            uv.x -= 0.25; // discard to zero
        }
        uv.y += 0.25;
    }

    float gridscale = 1.0;
    vec3 fp = vec3(fragPosition.x + 0.5, fragPosition.y, fragPosition.z + 0.5) * gridscale;
    vec3 fp_ceil = ceil(fp) / gridscale;

    // completely random texture
    //float randomValue = rand(fp_ceil);
    // texture based value
    vec2 ruv = abs(fract(fp_ceil.xy * 0.01));
    vec4 randomValues = texture2D(tex_noise0, ruv);
    float randomValue = randomValues.x;

    uv.x += ceil(randomValue * 4.0) * 0.25;

    vec4 color = texture2D(texture0, uv);

    gl_FragColor = vec4(color.rgb, 1.0);
}

