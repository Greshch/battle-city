#version 460
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colors;
out vec3 colors;
void main(){
    colors = vertex_colors;
    gl_Position = vec4(vertex_position, 1.0);   
}

#version 460
in vec3 colors;
out vec4 fragment_colors;
void main(){
    fragment_colors = vec4(colors, 1.0);   
}