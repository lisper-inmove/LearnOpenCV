# 色彩空间

> 文档版本：1.0
> 创建日期：2026-03-28
> 最后更新：2026-03-28
> 作者：Claude Code
> 项目：ImageJ 图片编辑工具

---

## 1. 概述

**色彩空间**（Color Space）是描述颜色的数学模型，它定义了如何用数值来表示颜色。在数字图像处理中，选择合适的色彩空间对于算法实现、性能优化和用户体验都至关重要。

在 ImageJ 项目中，理解不同色彩空间的特性对于以下功能实现具有重要意义：
- **颜色调整操作**：亮度、对比度、饱和度调整
- **图像转换**：彩色到灰度的转换、色彩空间转换
- **滤镜效果**：在不同色彩空间应用滤镜算法
- **图像分析**：颜色分割、特征提取
- **用户界面**：颜色选择器、颜色管理

## 2. 基本概念

### 2.1 什么是色彩空间？

色彩空间是一个三维或多维的坐标系系统，其中每个点代表一种颜色。常见的色彩空间包含以下组成部分：

1. **色彩模型**（Color Model）：定义色彩空间的数学结构
2. **基色**（Primaries）：构成色彩空间的基础颜色
3. **白点**（White Point）：定义为"白色"的颜色点
4. **伽马校正**（Gamma Correction）：亮度与数字值的非线性关系

### 2.2 色彩空间分类

| 分类 | 描述 | 示例 | 主要用途 |
|------|------|------|---------|
| **设备相关** | 依赖于具体设备的颜色重现能力 | RGB（显示器）、CMYK（打印机） | 设备颜色表示 |
| **设备无关** | 基于人眼感知，与设备无关 | CIELAB、CIEXYZ | 颜色测量与匹配 |
| **面向硬件** | 为特定硬件设计 | YUV（视频）、YCbCr（JPEG） | 视频压缩、传输 |
| **面向感知** | 符合人类颜色感知特性 | HSV、HSL、HSB | 用户界面、图像编辑 |

### 2.3 色彩深度与色域

- **色彩深度**（Color Depth）：每个颜色通道的位数（如8位/通道 = 24位RGB）
- **色域**（Gamut）：色彩空间能够表示的颜色范围
- **动态范围**（Dynamic Range）：最亮与最暗的比值

## 3. 常见色彩空间详解

### 3.1 RGB 色彩空间

**RGB**（Red, Green, Blue）是最常用的加色模型，基于三原色光的叠加。

#### 3.1.1 特性
- **加色模型**：光的叠加（R+G+B=白色）
- **设备相关**：依赖于显示设备的色域
- **线性关系**：数值与光强通常呈线性关系
- **通道相关**：各通道高度相关，改变亮度会影响颜色

#### 3.1.2 常见变体
- **sRGB**：标准RGB，最常用的网络和显示标准
- **Adobe RGB**：更大的色域，适合专业摄影
- **ProPhoto RGB**：极大的色域，适合高质量图像处理

#### 3.1.3 在ImageJ中的表示
```cpp
// Qt中的RGB表示
QRgb rgb = qRgb(255, 128, 0);  // 红色255, 绿色128, 蓝色0
int red = qRed(rgb);    // 255
int green = qGreen(rgb); // 128
int blue = qBlue(rgb);  // 0

// 带透明度的ARGB
QRgb argb = qRgba(255, 128, 0, 255);  // 添加Alpha通道
int alpha = qAlpha(argb);  // 255
```

#### 3.1.4 灰度转换算法
在T023任务中需要实现的灰度化操作：

1. **平均值法**：
   ```cpp
   gray = (R + G + B) / 3
   ```

2. **亮度法**（推荐）：
   ```cpp
   // ITU-R BT.601标准
   gray = 0.299 * R + 0.587 * G + 0.114 * B
   ```

3. **加权平均值法**：
   ```cpp
   // 可调节权重的版本
   gray = wR * R + wG * G + wB * B
   // 其中 wR + wG + wB = 1.0
   ```

### 3.2 HSV/HSL 色彩空间

**HSV**（Hue, Saturation, Value）和**HSL**（Hue, Saturation, Lightness）是面向感知的色彩空间，将颜色分解为更直观的分量。

#### 3.2.1 各分量含义
- **色相**（Hue）：颜色的基本属性（红、绿、蓝等），范围 0-360°
- **饱和度**（Saturation）：颜色的纯度，范围 0-100%
- **明度**（Value/Lightness）：颜色的亮度，范围 0-100%

#### 3.2.2 HSV vs HSL
| 特性 | HSV | HSL | 适用场景 |
|------|-----|-----|---------|
| **亮度定义** | 最大颜色分量 | 最大与最小分量的平均值 | HSV更适合图像处理 |
| **纯色亮度** | 不等（纯红色较暗） | 相等（所有纯色亮度相同） | HSL更适合UI设计 |
| **饱和度** | 相对最大分量的比例 | 相对亮度对称 | - |
| **几何模型** | 六棱锥 | 双六棱锥 | - |

#### 3.2.3 RGB ↔ HSV 转换算法

**RGB转HSV**：
```cpp
void rgbToHsv(int r, int g, int b, float& h, float& s, float& v) {
    float rn = r / 255.0f;
    float gn = g / 255.0f;
    float bn = b / 255.0f;

    float maxVal = std::max({rn, gn, bn});
    float minVal = std::min({rn, gn, bn});
    float delta = maxVal - minVal;

    // 计算明度
    v = maxVal;

    // 计算饱和度
    if (maxVal > 0.0f) {
        s = delta / maxVal;
    } else {
        s = 0.0f;
    }

    // 计算色相
    if (delta > 0.0f) {
        if (maxVal == rn) {
            h = 60.0f * fmod(((gn - bn) / delta), 6.0f);
        } else if (maxVal == gn) {
            h = 60.0f * (((bn - rn) / delta) + 2.0f);
        } else {
            h = 60.0f * (((rn - gn) / delta) + 4.0f);
        }
        if (h < 0.0f) h += 360.0f;
    } else {
        h = 0.0f;  // 无色相（灰度）
    }
}
```

**HSV转RGB**：
```cpp
void hsvToRgb(float h, float s, float v, int& r, int& g, int& b) {
    float c = v * s;  // 色度
    float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;

    float r1, g1, b1;
    if (h >= 0 && h < 60) {
        r1 = c; g1 = x; b1 = 0;
    } else if (h < 120) {
        r1 = x; g1 = c; b1 = 0;
    } else if (h < 180) {
        r1 = 0; g1 = c; b1 = x;
    } else if (h < 240) {
        r1 = 0; g1 = x; b1 = c;
    } else if (h < 300) {
        r1 = x; g1 = 0; b1 = c;
    } else {
        r1 = c; g1 = 0; b1 = x;
    }

    r = static_cast<int>((r1 + m) * 255);
    g = static_cast<int>((g1 + m) * 255);
    b = static_cast<int>((b1 + m) * 255);
}
```

#### 3.2.4 在ImageJ中的应用
1. **颜色选择器**：HSV/HSL更适合用户直观选择颜色
2. **颜色调整**：独立调整色相、饱和度、亮度
3. **图像处理**：在HSV空间进行滤波、分割等操作

### 3.3 YUV/YCbCr 色彩空间

**YUV**和**YCbCr**是用于视频和图像压缩的色彩空间，将亮度和色度信息分离。

#### 3.3.1 各分量含义
- **Y**：亮度（Luma）分量，包含图像的灰度信息
- **U/Cb**：蓝色色差（Blue - Y）
- **V/Cr**：红色色差（Red - Y）

#### 3.3.2 主要优势
1. **亮度-色度分离**：人类视觉对亮度更敏感，对色度较不敏感
2. **压缩友好**：可以对色度分量进行下采样（4:2:0, 4:2:2）
3. **兼容性**：向后兼容黑白电视（只使用Y分量）

#### 3.3.3 RGB ↔ YCbCr 转换（BT.601标准）

**RGB转YCbCr**：
```cpp
void rgbToYcbcr(int r, int g, int b, int& y, int& cb, int& cr) {
    // 标准化到[0,1]范围
    double rn = r / 255.0;
    double gn = g / 255.0;
    double bn = b / 255.0;

    // BT.601转换矩阵
    y  = static_cast<int>(16 + 65.481 * rn + 128.553 * gn + 24.966 * bn);
    cb = static_cast<int>(128 - 37.797 * rn - 74.203 * gn + 112.0 * bn);
    cr = static_cast<int>(128 + 112.0 * rn - 93.786 * gn - 18.214 * bn);

    // 钳制到有效范围
    y = std::clamp(y, 16, 235);
    cb = std::clamp(cb, 16, 240);
    cr = std::clamp(cr, 16, 240);
}
```

**YCbCr转RGB**：
```cpp
void ycbcrToRgb(int y, int cb, int cr, int& r, int& g, int& b) {
    // 转换为[0,1]范围
    double yn = (y - 16) / 219.0;
    double cbn = (cb - 128) / 224.0;
    double crn = (cr - 128) / 224.0;

    // 逆转换矩阵
    double rn = yn + 1.402 * crn;
    double gn = yn - 0.344136 * cbn - 0.714136 * crn;
    double bn = yn + 1.772 * cbn;

    // 钳制并转换回[0,255]
    r = static_cast<int>(std::clamp(rn, 0.0, 1.0) * 255);
    g = static_cast<int>(std::clamp(gn, 0.0, 1.0) * 255);
    b = static_cast<int>(std::clamp(bn, 0.0, 1.0) * 255);
}
```

#### 3.3.4 采样格式
| 格式 | 描述 | 存储需求 | 应用 |
|------|------|---------|------|
| **4:4:4** | 无下采样，全分辨率 | 100% | 高质量处理 |
| **4:2:2** | 水平方向2:1下采样 | 67% | 专业视频 |
| **4:2:0** | 水平和垂直都2:1下采样 | 50% | DVD、电视、JPEG |

#### 3.3.5 在ImageJ中的应用
1. **图像压缩**：JPEG使用YCbCr色彩空间
2. **视频处理**：如果需要支持视频文件
3. **亮度处理**：在Y通道进行直方图均衡化等操作

### 3.4 CIELAB 色彩空间

**CIELAB**（也称为Lab）是设备无关的色彩空间，基于人类视觉感知。

#### 3.4.1 各分量含义
- **L***：明度（Lightness），0=黑色，100=白色
- **a***：红-绿轴，正值偏红，负值偏绿
- **b***：黄-蓝轴，正值偏黄，负值偏蓝

#### 3.4.2 主要特性
1. **设备无关**：基于人眼感知，与设备无关
2. **感知均匀**：数值变化与感知变化大致成正比
3. **颜色差异度量**：ΔE可用于测量颜色差异

#### 3.4.3 在ImageJ中的应用
1. **颜色匹配**：精确的颜色比较和匹配
2. **图像质量评估**：客观的图像质量指标
3. **专业图像处理**：高质量的颜色调整

### 3.5 CMYK 色彩空间

**CMYK**（Cyan, Magenta, Yellow, Key/Black）是用于印刷的减色模型。

#### 3.5.1 特性
- **减色模型**：颜色通过吸收光线形成（C+M+Y=黑色）
- **用于印刷**：专为四色印刷设计
- **色域较小**：通常小于RGB色彩空间

#### 3.5.2 在ImageJ中的应用
1. **打印预览**：模拟印刷效果
2. **专业出版**：准备用于印刷的图像
3. **颜色分离**：生成分色版

## 4. 色彩空间转换

### 4.1 转换原则

1. **可逆性**：理想情况下转换应该是可逆的
2. **精度保持**：尽量减少转换过程中的精度损失
3. **性能考虑**：转换计算可能影响性能
4. **色域映射**：不同色彩空间色域不同，需要映射处理

### 4.2 转换策略

**直接转换**：
```cpp
// RGB -> HSV -> RGB
ColorRGB rgb1(255, 128, 0);
ColorHSV hsv = rgb1.toHSV();
ColorRGB rgb2 = hsv.toRGB();
// rgb1 应大致等于 rgb2
```

**中间表示**：
```cpp
// 使用中间浮点表示减少精度损失
struct ColorRGBf {
    float r, g, b;  // [0, 1]

    ColorHSVf toHSV() const {
        // 浮点转换，精度更高
    }
};
```

### 4.3 性能优化

1. **查找表**（LUT）优化：
   ```cpp
   // 预计算转换表
   static std::array<ColorHSV, 256*256*256> rgbToHsvTable;
   // 初始化时填充表格
   // 使用时直接查表
   ```

2. **SIMD优化**：
   ```cpp
   // 使用SSE/AVX指令集并行处理多个像素
   __m128 r = _mm_load_ps(r_data);
   __m128 g = _mm_load_ps(g_data);
   __m128 b = _mm_load_ps(b_data);
   // 并行计算
   ```

3. **多线程处理**：
   ```cpp
   // 分块并行转换
   #pragma omp parallel for
   for (int y = 0; y < height; y++) {
       // 处理一行
   }
   ```

## 5. 在ImageJ项目中的应用

### 5.1 颜色调整操作（T022任务）

在亮度/对比度调整功能中，选择合适的色彩空间至关重要：

#### 方案比较
| 方案 | 实现复杂度 | 效果质量 | 性能 | 推荐度 |
|------|-----------|---------|------|--------|
| **RGB空间调整** | 简单 | 颜色可能失真 | 快 | ★★☆☆☆ |
| **HSV空间调整** | 中等 | 保持色相，仅调整V | 中等 | ★★★★☆ |
| **YUV空间调整** | 中等 | 保持色度，仅调整Y | 快 | ★★★★★ |

#### 推荐实现：YUV空间调整
```cpp
class BrightnessContrastOperation : public EditOperation {
public:
    void Apply(QImage& image) override {
        // 转换为YUV空间
        QImage yuvImage = convertRgbToYuv(image);

        // 仅调整Y通道（亮度）
        adjustYChannel(yuvImage, brightness_, contrast_);

        // 转换回RGB
        image = convertYuvToRgb(yuvImage);
    }

private:
    float brightness_;  // -1.0 到 1.0
    float contrast_;    // -1.0 到 1.0
};
```

### 5.2 灰度化操作（T023任务）

如前所述，在RGB空间实现多种灰度转换算法。

### 5.3 颜色选择器实现

对于画笔工具（T035）和文字工具（T038）的颜色选择：

#### 推荐方案：HSV颜色选择器
```cpp
class ColorPickerDialog : public QDialog {
public:
    ColorPickerDialog(QWidget* parent = nullptr) {
        // HSV颜色轮
        huePicker_ = new HueWheelWidget(this);
        saturationValuePicker_ = new SaturationValueSquare(this);

        // RGB数值输入
        rgbSpinBoxes_[0] = new QSpinBox(this);  // R
        rgbSpinBoxes_[1] = new QSpinBox(this);  // G
        rgbSpinBoxes_[2] = new QSpinBox(this);  // B

        // HSV数值输入
        hsvSpinBoxes_[0] = new QSpinBox(this);  // H
        hsvSpinBoxes_[1] = new QSpinBox(this);  // S
        hsvSpinBoxes_[2] = new QSpinBox(this);  // V

        connect(huePicker_, &HueWheelWidget::hueChanged,
                this, &ColorPickerDialog::updateColor);
    }

private:
    void updateColor(float h, float s, float v) {
        // 更新所有表示形式
        QColor color = QColor::fromHsvF(h, s, v);

        // 更新RGB输入
        rgbSpinBoxes_[0]->setValue(color.red());
        rgbSpinBoxes_[1]->setValue(color.green());
        rgbSpinBoxes_[2]->setValue(color.blue());

        // 更新预览
        previewWidget_->setColor(color);
    }
};
```

### 5.4 魔术棒工具（T034任务）

基于颜色的区域选择需要考虑色彩空间：

#### 颜色相似度计算
```cpp
class MagicWandTool : public Tool {
public:
    void OnMousePress(const QPoint& pos) override {
        QColor targetColor = image_.pixelColor(pos);

        // 转换为Lab空间进行感知相似度计算
        ColorLab targetLab = convertToLab(targetColor);

        // 使用ΔE距离进行相似度判断
        for (int y = 0; y < image_.height(); y++) {
            for (int x = 0; x < image_.width(); x++) {
                QColor currentColor = image_.pixelColor(x, y);
                ColorLab currentLab = convertToLab(currentColor);

                float deltaE = calculateDeltaE(targetLab, currentLab);
                if (deltaE < tolerance_) {
                    // 选中该像素
                    selectedPixels_.emplace_back(x, y);
                }
            }
        }
    }

private:
    float tolerance_;  // 容差，基于ΔE单位
};
```

## 6. 性能优化建议

### 6.1 缓存转换结果

```cpp
class ColorSpaceCache {
public:
    // 缓存RGB到YUV的转换
    const QImage& getYuvImage(const QImage& rgbImage) {
        auto it = rgbToYuvCache_.find(rgbImage.cacheKey());
        if (it != rgbToYuvCache_.end()) {
            return it->second;
        }

        // 计算并缓存
        QImage yuvImage = convertRgbToYuv(rgbImage);
        rgbToYuvCache_[rgbImage.cacheKey()] = yuvImage;
        return rgbToYuvCache_[rgbImage.cacheKey()];
    }

private:
    std::unordered_map<qint64, QImage> rgbToYuvCache_;
};
```

### 6.2 渐进式转换

对于大图像，支持渐进式处理和预览：
```cpp
class ProgressiveColorConverter {
public:
    void startConversion(const QImage& source, ColorSpace targetSpace) {
        sourceImage_ = source;
        targetSpace_ = targetSpace;

        // 分块处理
        int blockSize = 64;
        for (int y = 0; y < source.height(); y += blockSize) {
            for (int x = 0; x < source.width(); x += blockSize) {
                // 处理一个块
                QRect blockRect(x, y,
                    std::min(blockSize, source.width() - x),
                    std::min(blockSize, source.height() - y));

                processBlock(blockRect);

                // 发出进度信号
                emit progressChanged(calculateProgress(x, y));
            }
        }
    }
};
```

### 6.3 硬件加速

考虑使用OpenGL着色器进行色彩空间转换：
```glsl
// GLSL着色器示例
uniform sampler2D rgbTexture;

void main() {
    vec3 rgb = texture2D(rgbTexture, texCoord).rgb;

    // RGB转YUV
    float y =  0.299 * rgb.r + 0.587 * rgb.g + 0.114 * rgb.b;
    float u = -0.147 * rgb.r - 0.289 * rgb.g + 0.436 * rgb.b;
    float v =  0.615 * rgb.r - 0.515 * rgb.g - 0.100 * rgb.b;

    gl_FragColor = vec4(y, u, v, 1.0);
}
```

## 7. 测试策略

### 7.1 单元测试

```cpp
TEST(ColorSpaceTest, RgbToHsvConversion) {
    // 测试边界值
    ColorRGB black(0, 0, 0);
    ColorHSV hsvBlack = black.toHSV();
    EXPECT_NEAR(hsvBlack.v, 0.0f, 0.01f);
    EXPECT_NEAR(hsvBlack.s, 0.0f, 0.01f);

    // 测试纯红色
    ColorRGB red(255, 0, 0);
    ColorHSV hsvRed = red.toHSV();
    EXPECT_NEAR(hsvRed.h, 0.0f, 1.0f);  // 0度
    EXPECT_NEAR(hsvRed.s, 1.0f, 0.01f);
    EXPECT_NEAR(hsvRed.v, 1.0f, 0.01f);

    // 测试可逆性
    ColorRGB original(128, 64, 192);
    ColorHSV converted = original.toHSV();
    ColorRGB restored = converted.toRGB();

    // 允许少量舍入误差
    EXPECT_NEAR(original.r, restored.r, 2);
    EXPECT_NEAR(original.g, restored.g, 2);
    EXPECT_NEAR(original.b, restored.b, 2);
}
```

### 7.2 性能测试

```cpp
TEST(ColorSpaceTest, ConversionPerformance) {
    QImage testImage(1920, 1080, QImage::Format_RGB32);
    testImage.fill(Qt::white);

    // 测试RGB->HSV转换性能
    auto start = std::chrono::high_resolution_clock::now();

    QImage hsvImage = convertRgbToHsv(testImage);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // 1080p图像应在100ms内完成
    EXPECT_LT(duration.count(), 100);
}
```

### 7.3 视觉测试

创建测试图像验证转换正确性：
```cpp
TEST(ColorSpaceTest, VisualVerification) {
    // 创建渐变测试图像
    QImage gradient(256, 256, QImage::Format_RGB32);
    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 256; x++) {
            gradient.setPixelColor(x, y, QColor(x, y, 128));
        }
    }

    // 转换并验证
    QImage hsvImage = convertRgbToHsv(gradient);

    // 验证特定属性
    // 例如：左上角应为低亮度，右下角应为高亮度
    QColor topLeft = hsvImage.pixelColor(0, 0);
    QColor bottomRight = hsvImage.pixelColor(255, 255);

    EXPECT_LT(topLeft.value(), bottomRight.value());
}
```

## 8. 扩展功能规划

### 8.1 颜色管理（Color Management）

支持ICC配置文件，实现准确的颜色重现：
```cpp
class ColorProfileManager {
public:
    void setSourceProfile(const IccProfile& profile);
    void setDisplayProfile(const IccProfile& profile);
    void setPrinterProfile(const IccProfile& profile);

    QImage applyColorConversion(const QImage& source);
};
```

### 8.2 色域警告

对于超出目标色域的颜色提供视觉反馈：
```cpp
class GamutWarningOverlay : public QWidget {
public:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);

        // 检查每个像素是否在目标色域内
        for (int y = 0; y < image_.height(); y++) {
            for (int x = 0; x < image_.width(); x++) {
                QColor color = image_.pixelColor(x, y);
                if (!isInGamut(color, targetGamut_)) {
                    // 绘制警告标记
                    painter.setPen(Qt::red);
                    painter.drawPoint(x, y);
                }
            }
        }
    }
};
```

### 8.3 高级颜色调整

基于色彩空间的高级调整工具：
- **色相/饱和度调整**：在HSV空间调整
- **颜色平衡**：在RGB或Lab空间调整
- **通道混合器**：自定义各通道贡献
- **颜色查找表**（LUT）：应用预设颜色风格

## 9. 总结与建议

### 9.1 色彩空间选择指南

| 应用场景 | 推荐色彩空间 | 原因 |
|---------|-------------|------|
| **用户颜色选择** | HSV/HSL | 直观，符合人类感知 |
| **亮度/对比度调整** | YUV | 亮度-色度分离，避免颜色失真 |
| **颜色相似度计算** | CIELAB | 感知均匀，ΔE距离有意义 |
| **图像压缩/保存** | YCbCr | 标准格式，兼容性好 |
| **专业颜色处理** | CIELAB | 设备无关，准确度高 |
| **打印输出** | CMYK | 印刷专用 |

### 9.2 在ImageJ中的实施优先级

1. **基础支持**（第一阶段）：
   - RGB处理（已支持）
   - 灰度转换（T023任务）
   - 简单颜色调整（RGB空间）

2. **高级支持**（第二阶段）：
   - HSV颜色选择器（画笔、文字工具）
   - YUV空间亮度调整（T022任务改进）
   - 色彩空间转换工具

3. **专业支持**（第三阶段）：
   - CIELAB颜色匹配
   - CMYK打印支持
   - ICC颜色管理

### 9.3 性能与质量平衡

1. **实时操作**：使用优化算法和查找表
2. **批量处理**：支持多线程和渐进式处理
3. **高质量输出**：使用浮点计算和设备无关色彩空间
4. **内存效率**：合理缓存，避免不必要的转换

### 9.4 学习资源

1. **书籍**：
   - 《色彩科学导论》
   - 《数字图像处理的颜色科学》
   - 《Computer Graphics: Principles and Practice》

2. **标准文档**：
   - ITU-R BT.601（SDTV标准）
   - ITU-R BT.709（HDTV标准）
   - sRGB标准（IEC 61966-2-1）

3. **开源项目参考**：
   - OpenCV色彩空间转换实现
   - ImageMagick颜色管理
   - Little CMS（色彩管理引擎）

---

## 附录：核心公式速查

### A.1 RGB ↔ YCbCr（BT.601）
```
Y  =  0.299R + 0.587G + 0.114B
Cb = -0.169R - 0.331G + 0.500B + 128
Cr =  0.500R - 0.419G - 0.081B + 128

R = Y + 1.403(Cr - 128)
G = Y - 0.344(Cb - 128) - 0.714(Cr - 128)
B = Y + 1.773(Cb - 128)
```

### A.2 RGB ↔ HSV
```
max = max(R, G, B)
min = min(R, G, B)
delta = max - min

V = max
S = (max > 0) ? delta / max : 0

if delta > 0:
    if max == R: H = 60 * (((G - B) / delta) mod 6)
    if max == G: H = 60 * (((B - R) / delta) + 2)
    if max == B: H = 60 * (((R - G) / delta) + 4)
else:
    H = 0
```

### A.3 ΔE（CIELAB颜色差异）
```
ΔE = sqrt((ΔL*)^2 + (Δa*)^2 + (Δb*)^2)

ΔE < 1.0: 人眼无法区分
ΔE 1.0-2.0: 专家可察觉
ΔE > 3.0: 普通人可察觉
```

### A.4 伽马校正
```
线性 → sRGB:
if linear ≤ 0.0031308:
    srgb = 12.92 * linear
else:
    srgb = 1.055 * linear^(1/2.4) - 0.055

sRGB → 线性:
if srgb ≤ 0.04045:
    linear = srgb / 12.92
else:
    linear = ((srgb + 0.055) / 1.055)^2.4
```

---

*本文档是 ImageJ 项目技术文档的一部分，将随着项目开发不断完善和更新。*

*更新日志：*
- **2026-03-28**：创建初始版本，包含完整色彩空间理论和实践指南。