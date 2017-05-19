# 画布操作       

## 1.位移(translate)    
```java
/**
     * Preconcat the current matrix with the specified translation
     *
     * @param dx The distance to translate in X
     * @param dy The distance to translate in Y
    */
    public void translate(float dx, float dy) {
        native_translate(mNativeCanvasWrapper, dx, dy);
    }
```    
这个位移指的是坐标系的移动，也可以看作是坐标原点的移动，屏幕默认坐标原点在左上角，但是我想在稍微靠近屏幕中间的位置画图      

```java
@Override
   protected void onDraw(Canvas canvas) {
       super.onDraw(canvas);
       mPaint.setColor(Color.BLACK);
       mPaint.setAntiAlias(true);
       mPaint.setStyle(Paint.Style.FILL);
       //第一个圆
       //translate移动画布中心，每次移动相对于当前位置，而不是相对与左上角坐标原点
       canvas.translate(200, 200);
       canvas.drawCircle(0, 0, 100, mPaint);

       //第二个圆
       mPaint.setColor(Color.BLUE);
       canvas.translate(200, 200);
       canvas.drawCircle(0, 0, 100, mPaint);
   }
```     
效果如图        

![](http://i2.muimg.com/588926/6413f9e051e3b51d.png)     

可以看到translate移动画布中心，每次移动相对于当前位置，而不是相对与左上角坐标原点，而且位移是可叠加的        

## 2.缩放(scale)     
有两个重要的方法       
```java
/**
    * Preconcat the current matrix with the specified scale.
    *
    * @param sx The amount to scale in X
    * @param sy The amount to scale in Y
    */
   public void scale(float sx, float sy) {
       native_scale(mNativeCanvasWrapper, sx, sy);
   }

   /**
    * Preconcat the current matrix with the specified scale.
    *
    * @param sx The amount to scale in X
    * @param sy The amount to scale in Y
    * @param px The x-coord for the pivot point (unchanged by the scale)
    * @param py The y-coord for the pivot point (unchanged by the scale)
    */
   public final void scale(float sx, float sy, float px, float py) {
       translate(px, py);
       scale(sx, sy);
       translate(-px, -py);
   }
```
