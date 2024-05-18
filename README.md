# RealTimeMapping
real time mapping using optical image with cpp


# ビルド
mkdir build
cmake ..
cmake --build .
./mosaic


## 構築手順
making
- opencv
https://takacity.blog.fc2.com/blog-entry-325.html


- ceres-solver
https://qiita.com/keita-n-ac/items/06f4214c7ae3292c5e44






### 環境構築参考
- ceres-solver ↓の人は 21.04
https://www.youtube.com/watch?v=BnxivTzczEY


#### glog のインストール
`
git clone https://github.com/google/glog.git
mkdir build
cd build
cmake ..
make
make install
`


`
### ceres-solver のインストール
git clone 
cd ceres-solver
mkdir build
cd build
cmake ..
apt-get install libmetiis-dev
make -j4
- make だとエラーが出る. -j4 とは何者
`


