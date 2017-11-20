import java.awt.image.BufferedImage;

/**
 * 对图像像素进行数学运算
 */
public class ImageMathOperation extends AbstractImageOption {
    //运算的类型
    protected static final int TYPE_ADD = 0;
    protected static final int TYPE_LESS = 1;
    protected static final int TYPE_MUTIPLY = 2;
    protected static final int TYPE_EXCEPT = 3;
    protected static final int TYPE_LOG = 4;
    protected static final int TYPE_SQUARE = 5;
    protected static final int TYPE_SQRT = 6;
    private int type;
    //像素加减乘除运算的尺度
    private int value;

    public ImageMathOperation() {
        this.type = 0;
        this.value = 20;
    }

    @Override
    public void process(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();
        int[] pixels = new int[width * height];
        int index = 0;
        getRGB(image, 0, 0, width, height, pixels);
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                index = row * width + col;
                int pixel = pixels[index];
                int pa = pixel >>> 24;//alpha
                int pr = (pixel >> 16) & 0xFF;
                int pg = (pixel >> 8) & 0xFF;
                int pb = (pixel) & 0xFF;

                //只对RGB三个通道进行运算
                pr = imageMath(pr);
                pg = imageMath(pg);
                pb = imageMath(pb);

                //将处理后的像素重新写回图片中
                pixels[index] = (pa << 24 | pr << 16 | pg << 8 | pb);
            }
        }
        setRGB(image, 0, 0, width, height, pixels);
    }

    private int imageMath(int pixel) {
        int result = 0;
        //log运算整体像素区间提升
        double range = (255 / Math.log(255));

        switch (type) {
            case TYPE_ADD:
                result = value + pixel;
                break;
            case TYPE_LESS:
                result = pixel - value;
                break;
            case TYPE_MUTIPLY:
                result = pixel * value;
                break;
            case TYPE_EXCEPT:
                result = pixel / value;
                break;
            case TYPE_LOG:
                result = (int) (pixel * range);
                break;
            case TYPE_SQUARE:
                //有的像素平方后会超出像素值范围，这里我们将值重新规划到像素值范围内
                result = (pixel * pixel) / 255;
                break;
            case TYPE_SQRT:
                result = (int) Math.sqrt(pixel);
                break;

        }

        //上面的简单四则运算如果运算的尺度很大的话也会超出像素值范围，这里我们做一下规划操作
        return (result < 0 ? 0 : (result > 255 ? 255 : result));
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
