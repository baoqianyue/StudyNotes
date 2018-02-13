# AsyncTask  
## 异步操作  
在软件运行中常会遇到一些耗时任务，如果不将这些任务放到子线程中去，就有可能导致主线程堵塞，针对这个问题，Android提供了一个异步处理消息机制。  
**常用来解决UI更新操作**  
## 具体实现  
* AsyncTask是个抽象类，所以我们必须创建一个子类去继承它，继承的同时要为这个类指定三个泛型参数：  
  * Params: 启动任务时需要传入的参数，比如HTTP请求的URL  
  * Progress: 后台任务执行的进度  
  * Result : 后台任务执行完成的结果  

* 重写父类方法   
  * onPreExecute()   
  在任务开始执行之前调用此方法，可以用来设置进度条  
  * doInBackground()   
  这个方法内的所有代码都是在子线程中执行的，是来完成任务的主要工作**但是不能直接更新UI**，可以调用publicProgress(Progress...)来更新进度   
  * onProgressUpdate(Progress...)   
  这个方法是在主线程中执行的，当调用了publicProgress(Progress...)后，这个方法很快会被调用，可以在这里进行进度条的数据读取操作，这里的参数就是从后台任务传过来的   
  * onPostExecute(Result)
  这个方法是在主线程中执行的，任务执行的结果以此方法的参数返回，可以根据这个结果进行一些UI操作   
  补充：这个方法会在```doInBackground()```方法执行完毕之后才会运行，更为重要的是，它是在主线程而非后台线程中运行的，因此在此方法中更新UI更为安全         
  ——————来自《Android权威编程指南》      
  * onCancelled()    
  当后台任务调用取消时，做的操作   


* 一个简单例子    



```java

public class DownloadTask extends AsyncTask<Void, Integer, Boolean> {
    private ProgressDialog progressDialog;


    @Override
    protected void onPreExecute() {
        progressDialog.show();
    }

    @Override
    protected Boolean doInBackground(Void... params) {
        try {
            while (true) {
                int downloadPercent = doDownload();//这是一个虚构的方法
                publishProgress(downloadPercent);
                if (downloadPercent >= 100) {
                    break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return true;
    }

    @Override
    protected void onProgressUpdate(Integer... values) {
        //在这里更新下载进度
        progressDialog.setMessage("Downloaded" + values[0] + "%");
    }

    @Override
    protected void onPostExecute(Boolean result) {
        //关闭进度条
        progressDialog.dismiss();
        //在这里提示下载结果
        if (result) {
            Toast.makeText(context, "Download succeed", Toast.LENGTH_SHORT);
        } else {
            Toast.makeText(context, "Download failed", Toast.LENGTH_SHORT);
        }
    }
}
```

## 注意事项  
* 不要手动调用onPreExecute(),doInBackground(),onProgressUpdate()这几个方法   
* 这个task只能执行一次   
