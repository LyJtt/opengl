#version 440 core
out vec4 FragColor;
in vec2 TexCord;
uniform sampler2D textureImg;
uniform sampler2D textureImg1;
uniform sampler2D textureImg2;
uniform float ratio;
void main(){
    FragColor = mix(texture(textureImg,TexCord),texture(textureImg2,TexCord),ratio);
}
