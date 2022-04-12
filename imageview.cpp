#include "imageview.h"
#include <QDebug>
#include <QPainter>

ImageView::ImageView(QWidget* parent)
    : QOpenGLWidget(parent)
{
    imageSourceData = nullptr;
    setAutoFillBackground(false);
}

ImageView::~ImageView()
{
#if USE_OPENGL
    glTexture->destroy();
#endif
}

// 设置待显示的数据源
void ImageView::setImage(uchar* imageSrc, uint width, uint height)
{
    imageSourceData = imageSrc;
    imageSize.setWidth(width);
    imageSize.setHeight(height);
    update();
}

void ImageView::setImage(const QImage& img)
{
    image = img;
    imageSourceData = (uchar*)image.bits();
    //    imageSize.setWidth(image.width());
    //    imageSize.setHeight(image.height());
    update();
}
#if USE_OPENGL
void ImageView::initializeGL()
{
    initializeOpenGLFunctions();
    glTexture = new QOpenGLTexture(QOpenGLTexture::Target2D);

    glTexture->create();
    glTextureID = glTexture->textureId();
    //    glBindTexture(GL_glTexture2D, glTextureID);
    //    glTexParameteri(GL_glTexture2D, GL_glTextureMAG_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_glTexture2D, GL_glTextureMIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, glTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ImageView::paintGL()
{
    static bool initTextureFlag = false;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (imageSourceData == nullptr) {
        return;
    }

    // glBindTexture(GL_glTexture2D, glTextureID);
    glBindTexture(GL_TEXTURE_2D, glTextureID);
    if (!initTextureFlag) {
        // 首次显示纹理
        // glTexImage2D(GL_glTexture2D, 0, GL_RGBA, imageSize.width(), imageSize.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageSourceData);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize.width(), imageSize.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageSourceData);

        initTextureFlag = true;
    } else {
        // 动态修改纹理数据
        // glTexSubImage2D(GL_glTexture2D, 0, 0, 0, imageSize.width(), imageSize.height(), GL_RGBA, GL_UNSIGNED_BYTE, imageSourceData);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imageSize.width(), imageSize.height(), GL_RGBA, GL_UNSIGNED_BYTE, imageSourceData);
    }

    // glEnable(GL_glTexture2D);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);

    //顶点坐标和纹理坐标必须一一对应
    glTexCoord2d(0.0f, 0.0f);
    glVertex2d(0, 0);
    glTexCoord2d(0.0f, 1.0f);
    glVertex2d(0, windowSize.height());
    glTexCoord2d(1.0f, 1.0f);
    glVertex2d(windowSize.width(), windowSize.height());
    glTexCoord2d(1.0f, 0.0f);
    glVertex2d(windowSize.width(), 0);
    glEnd();
    // glDisable(GL_glTexture2D);
    glDisable(GL_TEXTURE_2D);
}

void ImageView::resizeGL(int w, int h)
{
    windowSize.setWidth(w);
    windowSize.setHeight(h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowSize.width(), windowSize.height(), 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
#else
void ImageView::paintEvent(QPaintEvent* e)
{
    QPainter painter;

    painter.begin(this);
    painter.drawImage(rect(), image);

    painter.end();
}
#endif
