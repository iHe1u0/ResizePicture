#pragma once

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QWidget>

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
    void setImageData(uchar* imageSrc, uint width, uint height);
    void setImageData(const QImage& img);

protected:
    // 重写QGLWidget类的接口
#if USE_OPENGL
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
#else
    // 不需要时不能继承，否则会黑屏
    void paintEvent(QPaintEvent* e) override;
#endif

private:
    uchar* imageData_; //纹理显示的数据源
    QSize imageSize_; //图片尺寸
    QSize Ortho2DSize_; //窗口尺寸
    QOpenGLTexture* texture_;
    GLuint textureId_; //纹理对象ID
    int vertexPos_[Pos_Max]; //窗口坐标
    float texturePos_[Pos_Max]; //纹理坐标
    QImage m_img;
};
