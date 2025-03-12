set -x
#删除编译文件
rm -rf 'pwd'/build/*
cd 'pwd'/build &&
	cmake .. &&
	make
