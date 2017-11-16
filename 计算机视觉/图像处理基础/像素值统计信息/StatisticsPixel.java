import java.awt.image.BufferedImage;

public class StatisticsPixel extends AbstractImageOption {
    private int max;
    private int min;
    //均值
    private double means;
    //方差
    private double variance;

    public StatisticsPixel() {
        this.max = 0;
        this.min = 0;
        this.means = 0;
        this.variance = 0;
    }

    /**
     * 计算像素最值、均值和标准差
     * @param image
     */
    @Override
    public void process(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();
        int[] pixels = new int[width * height];
        getRGB(image, 0, 0, width, height, pixels);
        int index = 0;
        double num = 0;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                index = row * width + col;
                int pixel = pixels[index];
                //因为灰度图的各通道的像素值都一样，这里我们只计算出一个通道的像素值即可
                int pr = pixel >> 16 & 0xFF;
                //像素最大值
                max = Math.max(max, pr);
                //像素最小值
                min = Math.min(min, pr);
                //像素总和
                num += pr;
            }
        }
        //像素均值
        means = num / (width * height);
        System.out.println("max:" + max);
        System.out.println("min:" + min);
        System.out.println("means:" + means);

        /**
         * 计算标准差
         */
        num = 0;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                index = row * width + col;
                int pixel = pixels[index];
                //因为灰度图的各通道的像素值都一样，这里我们只计算出一个通道的像素值即可
                int pr = pixel >> 16 & 0xFF;
                num = Math.pow((pr - means), 2);
            }
        }
        int len = width * height;
        variance = Math.sqrt(num / len);
        System.out.println("variance:" + variance);

        /**
         * 通过均值实现图像的二值化
         */
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                index = row * width + col;
                int pixel = pixels[index];
                int pr = pixel >> 16 & 0xFF;
                //进行二值化操作
                if (pr > means) {
                    pr = 255;
                } else {
                    pr = 0;
                }
                //将各通道像素装载起来，重新写入
                //灰度图alpha通道值都为255
                pixels[index] = (255 << 24 | pr << 16 | pr << 8 | pr);
            }
        }
        setRGB(image, 0, 0, width, height, pixels);
    }


    public int getMax() {
        return max;
    }

    public void setMax(int max) {
        this.max = max;
    }

    public int getMin() {
        return min;
    }

    public void setMin(int min) {
        this.min = min;
    }

    public double getMeans() {
        return means;
    }

    public void setMeans(double means) {
        this.means = means;
    }

    public double getVariance() {
        return variance;
    }

    public void setVariance(double variance) {
        this.variance = variance;
    }
}
