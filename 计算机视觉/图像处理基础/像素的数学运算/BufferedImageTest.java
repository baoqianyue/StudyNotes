import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;


public class BufferedImageTest extends JComponent implements ActionListener {

    private BufferedImage image;
    private JButton processBtn;

    public BufferedImageTest(BufferedImage image) {
        this.image = image;
    }

    public JButton initView() {
        processBtn = new JButton("处理像素");
        processBtn.addActionListener(this);
        return processBtn;
    }

    /**
     * 绘制图片
     *
     * @param g
     */
    @Override
    protected void paintComponent(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        if (image != null) {
            g2d.drawImage(image, 0, 0, image.getWidth(), image.getHeight(), null);
        }
    }


    /**
     * 具体的对像素的操作
     */
    public void process() {
        ImageMathOperation imageMathOperation = new ImageMathOperation();
        imageMathOperation.setValue(20);
        imageMathOperation.setType(ImageMathOperation.TYPE_LESS);
        imageMathOperation.setType(ImageMathOperation.TYPE_MUTIPLY);
        imageMathOperation.setType(ImageMathOperation.TYPE_EXCEPT);
        imageMathOperation.setType(ImageMathOperation.TYPE_LOG);
        imageMathOperation.setType(ImageMathOperation.TYPE_SQUARE);
        imageMathOperation.setType(ImageMathOperation.TYPE_SQRT);
        imageMathOperation.setType(ImageMathOperation.TYPE_ADD);
        imageMathOperation.process(image);
    }


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
        if (type == BufferedImage.TYPE_INT_ARGB || type == BufferedImage.TYPE_INT_RGB) {
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


    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == processBtn) {
            //如果点击就处理像素
            //处理之后重新绘制图片
            this.process();
            this.repaint();

        }
    }


    public static void main(String[] args) {
        File file = new File("C:\\Users\\22876\\Desktop\\test.png");
        try {
            BufferedImage image = ImageIO.read(file);
            BufferedImageTest imagePanel = new BufferedImageTest(image);
            JFrame frame = new JFrame();
            frame.getContentPane().add(imagePanel, BorderLayout.CENTER);
            frame.getContentPane().add(imagePanel.initView(), BorderLayout.SOUTH);
            frame.setSize(500, 700);
            frame.setTitle("Barack");
            frame.setVisible(true);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
