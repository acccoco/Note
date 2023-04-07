
### 限制 cpu
```shell
ffmpeg -i input.xxx -threads 2 output.xxx
```


### 提取音频
```shell
ffmpeg -i <视频文件名> -vn -codec copy <输出文件名.m4a>
# -vn 表示不处理视频
# 后缀最好是 m4a
```


### 合并视频和音频
```shell
ffmpeg -i <video_file> <audio_file> -vcodec coopy -acodec copy <output_file>
# -vcodec 表示如何进行视频编码
# -acodec 表示如何进行音频编码
```


### 视频编码转换
```shell
ffmpeg -i <video_file> -vcodec <目标编码> <output_file>
# -vcodec 指定目标编码，比如 libx264，表示 H.264 编码

# MAC 平台可以使用 videotoolbox 硬件加速（顺便 bitrate 2000K）
-i <input> -c:v h264_videotoolbox -b:v 2000K <output>
```


### 视频剪切
```shell
# 第一种方法
ffmpeg -i <video_file> -ss <开始时间/hh:mm:ss> -t <持续时间/s> <output_file>

# 第二种方法
ffmpeg -i <video_file> -ss <开始时间> -to <结束时间/hh:mm:ss> <output_file>
```


### 文件合并
准备合并列表：`list.txt`，注意文件名放在单引号里面
```
file '1.mp4'
file '2.mp4'
```

执行命令
```shell
ffmpeg -f concat -safe 0 -i list.txt -c copy output.mp4
```


### 视频分辨率
```shell
ffmpeg -i input.mp4 -vf scale=1920:1080 output.mp4
```


### 视频转 gif
```shell
ffmpeg -i xxx.mp4 xxx.gif
```
