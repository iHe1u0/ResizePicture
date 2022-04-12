#include "imageview.h"

#include <QDebug>
#include <QPainter>

ImageView::ImageView(QWidget* parent)
    : QOpenGLWidget(parent)
{
    imageData_ = nullptr;
    setAutoFillBackground(false);
}

ImageView::~ImageView()
{
#if USE_OPENGL
    texture_->destroy();
#endif
}

// 设置待显示的数据源
void ImageView::setImageData(uchar* imageSrc, uint width, uint height)
{
    imageData_ = imageSrc;
    imageSize_.setWidth(width);
    imageSize_.setHeight(height);
    update();
}

void ImageView::setImageData(const QImage& img)
{
    m_img = img;
    imageData_ = (uchar*)m_img.bits();
    imageSize_.setWidth(m_img.width());
    imageSize_.setHeight(m_img.height());
    update();
}
#if USE_OPENGL
void ImageView::initializeGL()
{
    initializeOpenGLFunctions();
    texture_ = new QOpenGLTexture(QOpenGLTexture::Target2D);

    texture_->create();
    textureId_ = texture_->textureId();
    glBindTexture(GL_TEXTURE_2D, textureId_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

// cpu:4% gpu:10%
void ImageView::paintGL()
{
    static bool initTextureFlag = false;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (imageData_ == nullptr) {
        return;
    }

    // QByteArray ba((const char*)imageData_,64);
    // qDebug() <<imageData_ << ba;
    glBindTexture(GL_TEXTURE_2D, textureId_);

    if (!initTextureFlag) {
        // 首次显示纹理
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize_.width(), imageSize_.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData_);
        initTextureFlag = true;
    } else {
        // 动态修改纹理数据
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imageSize_.width(), imageSize_.height(), GL_RGBA, GL_UNSIGNED_BYTE, imageData_);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize_.width(), imageSize_.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData_);
    }

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);

    //顶点坐标和纹理坐标必须一一对应
    glTexCoord2d(0.0f, 0.0f);
    glVertex2d(0, 0);
    glTexCoord2d(0.0f, 1.0f);
    glVertex2d(0, Ortho2DSize_.height());
    glTexCoord2d(1.0f, 1.0f);
    glVertex2d(Ortho2DSize_.width(), Ortho2DSize_.height());
    glTexCoord2d(1.0f, 0.0f);
    glVertex2d(Ortho2DSize_.width(), 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void ImageView::resizeGL(int w, int h)
{
    Ortho2DSize_.setWidth(w);
    Ortho2DSize_.setHeight(h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Ortho2DSize_.width(), Ortho2DSize_.height(), 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
#else
void ImageView::paintEvent(QPaintEvent* e)
{
#if !USE_WIDGET_PAINT_WITHOUT_OPENGL
    QPainter p;

    p.begin(this);
    p.drawImage(rect(), m_img);

    p.end();
#endif
}
#endif
