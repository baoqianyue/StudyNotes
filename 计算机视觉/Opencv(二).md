## 调整像素范围     

```
saturate_cast<uchar> (-100) 返回0
saturate_cast<uchar> (288) 返回255
saturate_cast<uchar> (100) 返回100   
确保RGB值处在0~255范围内
```


## 读取像素     

### 通过指针访问          
  这种方法最快     

  举个例子            
  ```
  Mat image = imread(文件名);
  //行数
  int row = image.rows;
  //列数(本来的列数x图像通道数)    
  int col = image.cols * image.channels();

  //遍历所有像素
  for(int i = 0; i < row; i++)
  {
    //获取每一行像素的首地址     
    uchar* data = image.ptr<uchar>(i);

    for(int j = 0; j < col; j++)
    {
      //读取每个像素值
      cout << data[j] << endl;
    }
  }
  ```        

  Mat类提供了ptr函数可以得到图像任意行的首地址。             


  ***    


## 尺寸调整: resize()函数          

  函数原型    
  ```c++
  void resize(InputArray src, OutputArray dst, Size dsize, double fx = 0, double fy = 0, int interpolation = INTER_LINEAR);
  ```     

  第一个参数就是输入图像，Mat类的对象        

  第二个参数为输出图像，其不为零时，其尺寸为第三个参数的值dsize,或者通过src.size()计算出来         

  第三个参数为输出图像的大小，如果它为零，其值通过下式计算    

  ```
  dsize=Size(round(fx∗src.cols),round(fy∗src.rows))      
  这里，dsize,fx,fy都不能为零
  ```      

  第四个参数为沿着水平轴的缩放系数，默认值为0，当期为0时，通过下式计算     

  ```
  fx=(double)dsize.width/src.cols
  ```    

  第五个参数为沿着垂直轴的缩放系数，默认值为0，当其为0时，通过下式计算       

  ```
  fy=(double)dsize.height/src.rows
  ```     

  第六个参数用来指定插值方式，默认为INTER_LINEAR(线性插值)             
  其可选值为:         

  INTER_NEAREST最近邻插值

  目标如下的像素点为对应的最近的原图像的像素点。假设原图像大小为(s_height, s_width)，目标图像大小为(d_height, d_width)，那么高度和宽度的缩放比例为h_ratio = s_height/d_height，w_ratio=s_width/d_width。

  对面目标图像像素:(x, y)其值等于原图像(x * w_ration, y * h_ration)处的值。

  INTER_LINEAR 线性插值

  默认使用。在使用最近邻插值时，得到的坐标未必是一个整数，例如
  (xw_ration, yh_ration)=（10.5， 20.5），那么可能取得坐标点就有四种（10， 20）、（11， 20）、（10， 21）、（11， 21）。双线性插值，会把这四个坐标的像素值加权求和。
  D(x, y) = S(j, k) * w1 + S(j+1, k) w2 + S(j+1,k+1) w3 + S(j, K+1) * w4，其中w为权值。权值大小和计算位置的小数部分有关。

  CV_INTER_AREA：区域插值

  区域插值分为3种情况。图像放大时类似于线性插值，图像缩小时可以避免波纹出现。

  INTER_CUBIC 三次样条插值

  使用4x4邻域内的像素双3次插值。

  INTER_LANCZOS4 Lanczos插值

  使用8×8像素邻域的Lanczos插值  


  ***

  ## 绘制关键点: drawKeypoints()函数           

  函数原型       

  ```c++
  void drawKeypoints(const Mat& image, const vector<KeyPoint>& keypoints, Mat& outImage,
  const Scalar& color=Scalar::all(-1), int flags = DrawMatchesFlags::DEFAULT)     
  ```     

  第一个参数为输入图像，第二个参数为根据原图得到特征点，第三个参数为输出图像，它取决于第五个参数的取值，第四个参数为关键点的颜色，
  有默认值Scalar::all(-1),第五个参数为绘制关键点的特征标识符，有默认值          


  ## 专为特征点检测的点: KeyPoint类     

  ```c++
  class KeyPoint
  {
    Point2f pt;//坐标
    float size;//特征点领域直径
    float angle;//特征点的方向
    float response;
    int octave;//特征点所在的图像金字塔的组
    in class_id;//用于聚类的id
  }
  ```    
