package image;

import java.awt.image.BufferedImage;

/**
 * 调节图像总体的像素值范围，即从0~255的范围进行改变，从而达到图像整体色彩的改变
 */
public class ColorAdjustment extends AbstractImageOption {
    private float minValue;//这里可以由我们指定
    private float maxValue;//这里可以由我们指定
    private float defaultMinValue;//默认为0
    private float defaultMaxValue;//默认为255
    private float brightValue;//调节图像亮度的参数
    private int[] lut;//使用查找表提高色彩调节的效率
    private boolean isBright;

    public ColorAdjustment() {
        defaultMaxValue = 255;
        defaultMinValue = 0;
        minValue = 0;
        maxValue = 255;
        isBright = true;
    }

    public void setIsBright(boolean isBright) {
        this.isBright = isBright;
    }

    public void setBrightValue(float brightValue) {
        this.brightValue = brightValue;
    }

    public void setMinValue(float minValue) {
        this.minValue = minValue;
    }

    public void setMaxValue(float maxValue) {
        this.maxValue = maxValue;
    }

    @Override
    public void process(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();
        int[] pixels = new int[width * height];
        getRGB(image, 0, 0, width, height, pixels);
        int index = 0;
        if (isBright == true) {
            setBrightnessLut();
        } else {
            setUpMinMaxLut();
        }
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                index = row * width + col;
                int pixel = pixels[index];
                int pa = (pixel >> 24) & 0xff;
                int pr = (pixel >> 16) & 0xff;
                int pg = (pixel >> 8) & 0xff;
                int pb = (pixel) & 0xff;
                //使用查找表
                pixels[index] = (pa << 24 | lut[pr] << 16 | lut[pg] << 8 | lut[pb]);
            }
        }
        setRGB(image, 0, 0, width, height, pixels);
    }

    private void setUpMinMaxLut() {
        float min = defaultMinValue + minValue * (defaultMaxValue - defaultMinValue) / 255;
        float max = defaultMinValue + maxValue * (defaultMaxValue - defaultMinValue) / 255;
        System.out.println("min:" + min + "max:" + max);
        lut = new int[256];
        for (int i = 0; i < 256; i++) {
            float temp = i - min;
            float delta = max - min;
            //将计算后的结果写入查找表中
            int v = (int) ((temp / delta) * 256);//temp/delta的范围在0~1之间，最大值看作是0.999999...,
            //如果乘上255，那修改后的像素最大值就成了254.xxxx，int取整后为254，所以为了保证像素值最大值仍为255,这里乘上了256
            if (v < 0) {
                v = 0;
            }
            if (v > 255) {
                v = 255;
            }
            lut[i] = v;
        }
    }

    private void setBrightnessLut() {
        float center = defaultMinValue + (defaultMaxValue - defaultMinValue) * ((256 - brightValue) / 256);
        float min = defaultMinValue + minValue * (defaultMaxValue - defaultMinValue) / 255;
        float max = defaultMinValue + maxValue * (defaultMaxValue - defaultMinValue) / 255;
        float delta = max - min;
        min = center - delta / 2.0f;
        max = center + delta / 2.0f;

        System.out.println("min:" + min + "max: " + max);
        lut = new int[256];
        for (int i = 0; i < 256; i++) {
            float temp = i - min;
            float delta1 = max - min;
            int v = (int) ((temp / delta1) * 256);
            if (v < 0) {
                v = 0;
            }
            if (v > 255) {
                v = 255;
            }
            lut[i] = v;
        }
    }
}
