#!/bin/bash

# 此脚本用于删除当前目录下的 buildTest 文件夹，然后创建一个空的 buildTest文件夹

rm -rf buildTest
echo "buildTest deleted"
mkdir buildTest
echo "buildTest created"
