#version 330 core
layout (location = 0) in vec3 aPos;// the position variable has attribute position 0

out vec4 vertexColor;// specify a color output to the fragment shader

float random (vec3 st) {
    return fract(sin(dot(st.xyz, vec3(12.9898, 78.233, 54.53))) * 43758.5453);
}

void main()
{
    gl_Position = vec4(aPos, 1.0);// see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(random(aPos), random(aPos + vec3(1.0)), random(aPos + vec3(2.0)), 1.0);// set the output variable to a dark-red color
}
