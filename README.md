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



ceres-solver
- (参考) http://ceres-solver.org/installation.html
- (参考) https://qiita.com/keita-n-ac/items/06f4214c7ae3292c5e44
`
apt-get install -y libgoogle-glog-dev libgflags-dev
apt-get install -y libatlas-base-dev
apt-get install -y libeigen3-dev
apt-get install -y libsuitesparse-dev

git clone https://ceres-solver.googlesource.com/ceres-solver -b 2.2.0

mkdir ceres-bin
cd ceres-bin
cmake ../ceres-solver-2.2.0
make -j3
make test
# Optionally install Ceres, it can also be exported using CMake which
# allows Ceres to be used without requiring installation, see the documentation
# for the EXPORT_BUILD_DIR option for more information.
make install
`






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


