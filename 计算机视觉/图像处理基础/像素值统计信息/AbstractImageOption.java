import java.awt.image.BufferedImage;

public abstract class AbstractImageOption {

    //定义一个抽象的process方法，方便后面多样性的对像素的操作
    public abstract void process(BufferedImage image);


    /**
     * 通过IO流将一个图片的所有像素值提取
     *
     * @param image
     * @param x
     * @param y
     * @param width
     * @param height
     * @param pixels
     * @return
     */
    public static int[] getRGB(BufferedImage image, int x, int y, int width, int height, int[] pixels) {
        int type = image.getType();
        if (type == BufferedImage.TYPE_INT_ARGB || type ==   BufferedImage.TYPE_INT_RGB) {
            //如果想要得到ARGB/RGB这种通道类型的像素，我们就需要使用Raster来读取
            //Raster相当于一个像素工厂，我们将一些参数传进去就能拿到三或四通道的像素数据，然后转成整形数组
            return (int[]) image.getRaster().getDataElements(x, y, width, height, pixels);
        }
        return image.getRGB(x, y, width, height, pixels, 0, width);
    }

    /**
     * 传入像素数据组装图片
     *
     * @param image
     * @param x
     * @param y
     * @param width
     * @param height
     * @param pixels
     */
    public static void setRGB(BufferedImage image, int x, int y, int width, int height, int[] pixels) {
        int type = image.getType();
        if (type == BufferedImage.TYPE_INT_ARGB || type == BufferedImage.TYPE_INT_RGB) {
            image.getRaster().setDataElements(x, y, width, height, pixels);
        } else {
            image.setRGB(x, y, width, height, pixels, 0, width);
        }
    }
}
