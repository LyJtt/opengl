#version 440 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCord;
uniform sampler2D textureImg;
uniform sampler2D textureImg1;
void main(){
    FragColor = mix(texture(textureImg,TexCord),
            texture(textureImg1,TexCord),0.5);
}
