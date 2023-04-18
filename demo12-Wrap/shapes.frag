#version 440 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCord;
uniform sampler2D textureImg;
uniform sampler2D textureImg1;
uniform sampler2D textureImg2;
void main(){
    FragColor = texture(textureImg2,TexCord);
}
