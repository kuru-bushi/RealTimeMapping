```

$ cd <opencv_build_directory>
$ cmake -DOPENCV_EXTRA_MODULES_PATH=<opencv_contrib>/modules <opencv_source_directory>
$ make -j5
### 次
$ sudo make install

$ sudo ldconfig
```