### 概要
環境構築手順を下記に記載する

### 環境
ディストリビューションとライブラリ
```
# Docker
Docker version 24.0.6

# コンテナのディストリビューションとライブラリ
NAME="Ubuntu"
VERSION="20.04.6 LTS (Focal Fossa)"

cmake version 3.16.3
gcc (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0
g++ (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0
```

VSCode 拡張機能
```
CMake Tools
Dev Containers
GitLens
```


外部ライブラリを入れた後のディレクトリの構造
```
Src
    ├── ceres-bin
    ├── ceres-solver
    ├── ceres-solver
    ├── opencv-bin
    ├── opencv
    ├── opencv
    ├── CMakeLists.txt
    ├── hello.cpp
    └── main.cpp
```



### 構築手順
1. コンテナの作成
2. コンテナ内でライブラリのビルド

#### docker container の作成
```
cd Src
docker compose build
docker compose up -d
```
#### opencv

[公式 document](https://docs.opencv.org/4.5.5/d7/d9f/tutorial_linux_install.html), 
[参考記事1](https://takacity.blog.fc2.com/blog-entry-325.html), 
[参考記事2](https://www.kkaneko.jp/tools/ubuntu/ubuntu_opencv.html)

```
git clone -b 4.9.0  https://github.com/opencv/opencv.git
# 圧縮したソース https://github.com/opencv/opencv/releases/tag/4.9.0
mkdir opencv-bin
cd opencv-bin
cmake ../opencv
cmake --build .
make install
```

#### ceres-solver

[公式 document](http://ceres-solver.org/installation.html), 
[参考記事1](https://qiita.com/keita-n-ac/items/06f4214c7ae3292c5e44)
[参考記事2](https://ltslam-doc.readthedocs.io/en/latest/tutorial/ceres/ceres_solver_tutorial.html)

```
apt-get install -y libgoogle-glog-dev libgflags-dev
apt-get install -y libatlas-base-dev
apt-get install -y libeigen3-dev
apt-get install -y libsuitesparse-dev

git clone https://ceres-solver.googlesource.com/ceres-solver -b 2.2.0

mkdir ceres-bin
cd ceres-bin
cmake ../ceres-solver
make -j3
make test
# Optionally install Ceres, it can also be exported using CMake which
# allows Ceres to be used without requiring installation, see the documentation
# for the EXPORT_BUILD_DIR option for more information.
make install
```


### 環境構築が完了したか確認用のコマンド
```
cd Src
mkdir build && cd build
cmake ..
cmake --build .
./hello
```


### その他ナレッジ
- 使いたい外部ライブラリがすべてそろっている docker image を探すのは時間がかかりすぎる。まっさらな状態から作成するほうが速くできる。
- 他のディストリビューションで環境構築する場合の検索キーワード
```
{ディストリビューション名} how to install
```
- 参考になるかもしれないコマンドなど
```
### 環境構築参考
- ceres-solver ↓の人は 21.04
https://www.youtube.com/watch?v=BnxivTzczEY

#### glog のインストール

git clone https://github.com/google/glog.git
mkdir build
cd build
cmake ..
make
make install

### ceres-solver のインストール
git clone 
cd ceres-solver
mkdir build
cd build
cmake ..
apt-get install libmetiis-dev
make -j4
```
