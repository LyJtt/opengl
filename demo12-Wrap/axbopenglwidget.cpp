#include "axbopenglwidget.h"

unsigned int VBO, VAO, EBO;


float vertices[] = {
    //position        //colors        //texture coords
    0.9f, 0.9f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,//右上
    0.9f, -0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,//右下
    -0.9f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,//左下
    -0.9f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f//左上
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};


AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

AXBOpenGLWidget::~AXBOpenGLWidget()
{
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);
    doneCurrent();
}

void AXBOpenGLWidget::drawShape(Shape shape)
{
    m_shape = shape;
    update();
}

void AXBOpenGLWidget::setWireframe(bool wireframe)
{
    makeCurrent();
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    update();
    doneCurrent();
}

void AXBOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //创建VBO和VAO对象，并赋予ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //绑定VBO和VAO对象
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储。
    //如果data不是NULL，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    //glBindVertexArray(0);

    bool success;
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shapes.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shapes.frag");
    success = shaderProgram.link();
    if(!success)
        qDebug()<<"ERR:"<<shaderProgram.log();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //用线条来填充

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    textureImg = new QOpenGLTexture(QImage(":/images/images/hutaoyao.jpg").mirrored());
    textureImg1 = new QOpenGLTexture(QImage(":/images/images/hutaoqiqi.jpg").mirrored());
    textureImg2 = new QOpenGLTexture(QImage(":/images/images/hutaogui.jpg").mirrored());

    shaderProgram.bind();
    shaderProgram.setUniformValue("textureImg",0);
    shaderProgram.setUniformValue("textureImg1",1);
    shaderProgram.setUniformValue("textureImg2",2);
    textureImg2->generateMipMaps();
    glBindVertexArray(0);

    textureImg2->bind(2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void AXBOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void AXBOpenGLWidget::paintGL()
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();

    glBindVertexArray(VAO);

    switch(m_shape){
    case Rect:
        //glActiveTexture(GL_TEXTURE0);
        textureImg->bind(0);
        //glActiveTexture(GL_TEXTURE1);
        textureImg1->bind(1);
        textureImg2->bind(2);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        break;
    default:
        break;
    }

}
