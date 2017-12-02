package image;

import java.awt.image.BufferedImage;

/**
 * Created by BarackBao on 2017/12/1.
 */

public class ColorFill extends AbstractImageOption {

    //要填充的资源色块
    private BufferedImage colorRes;

    //颜色查找表
    private int[] table;


    public BufferedImage getColorRes() {
        return colorRes;
    }

    public void setColorRes(BufferedImage colorRes) {
        this.colorRes = colorRes;
    }

    @Override
    public void process(BufferedImage image) {
        setColorLookupTable();
        int width = image.getWidth();
        int height = image.getHeight();
        int[] pixels = new int[width * height];
        getRGB(image, 0, 0, width, height, pixels);
        int index;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                //因为是灰度图，所以这里只提取一个通道的像素
                index = row * width + col;
                int pixel = pixels[index];
                System.out.println(pixel);
                int pr = (pixel >> 16) & 0xFF;
                pixels[index] = table[pr];
            }
        }
        setRGB(image, 0, 0, width, height, pixels);
    }

    /**
     * 建立查找表
     */
    private void setColorLookupTable() {
        int width = colorRes.getWidth();
        int height = colorRes.getHeight();
        int[] pixels = new int[width * height];
        getRGB(colorRes, 0, 0, width, height, pixels);
        int index;
        //查找表
        table = new int[256];
        //因为色块在垂直方向是均匀分布的，所以这里为了像素的准确性，我们提取最中间一行的像素值做查找表
        int row = height / 2;
        //错开图片边缘的一些杂色
        for (int col = 4; col < 260; col++) {
            index = row * width + col;
            int pixel = pixels[index];
            table[col - 4] = pixel;
        }
    }
}
