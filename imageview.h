#pragma once

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QWidget>
#include <gl/GL.h>

class ImageView : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    enum {
        Left_Bottom_X,
        Left_Bottom_Y,
        Right_Bottom_X,
        Right_Bottom_Y,
        Right_Top_X,
        Right_Top_Y,
        Left_Top_X,
        Left_Top_Y,
        Pos_Max
    };

    ImageView(QWidget* parent = nullptr);
    ~ImageView();

    // 设置实时显示的数据源
    void setImage(uchar* imageSrc, uint width, uint height);
    void setImage(const QImage& img);

protected:
#if USE_OPENGL
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

#else
    // 不需要时不能继承，否则会黑屏
    void paintEvent(QPaintEvent* e) override;
#endif

private:
    //纹理显示的数据源
    uchar* imageSourceData;

    //图片尺寸
    QSize imageSize;

    //窗口尺寸
    QSize windowSize;

    QOpenGLTexture* glTexture;

    //纹理对象ID
    GLuint glTextureID;

    //窗口坐标
    int vertexPos[Pos_Max];

    //纹理坐标
    float glTexturePos[Pos_Max];

    QImage image;
};
