#!/bin/bash

#判断上级目录是否为空
ifeq (,$(PROJECT_DIR))
CURRENT_DIR := $(shell pwd)
PROJECT_DIR := $(shell pwd)/..
else
CURRENT_DIR := $(PROJECT_DIR)/app1
endif
 
########### 编译APP1所需源文件,依需修改添加 #############
#源文件位置
OBJS := $(CURRENT_DIR)/src/main.c
#OBJS += $(CURRENT_DIR)/src/function_1.c
#OBJS += $(CURRENT_DIR)/src/function_2.c
#OBJS += $(CURRENT_DIR)/src/function_3.c
 
#编译头文件路径
CFLAG := -Wall -W -Os -g -I $(CURRENT_DIR)/include/
LFLAG=-L$(CURRENT_DIR)/lib -lpaho-mqtt3c 
#-lpaho-mqtt3a 
#头文件路径增加
#APP1_INCLUDE_PATH += -I $(TOP_DIR)/public_include
 

CC := arm-linux-gnueabihf-gcc
TARGET := $(CURRENT_DIR)/app1-arm


 
#交换软件版本定义，以修改时间为版本号
ifeq (,$(APP_VER))
APP_VER := V-21.03.22.01
endif
 
#获取编译的时间
GET_DATE := $(shell date +%F)
GET_TIME := $(shell date +%H:%M:%S)
 
######## Makefile传递给C文件的宏定义 ########
#编译时间
MAKE_DEFINE := -D MAKE_TIME=\"$(GET_DATE)\ $(GET_TIME)\"
 
#DEBUG模式是否打开 DEBUG_CMD
ifeq ($(DEBUG),ON)
MAKE_DEFINE += -D DEBUG
MAKE_DEFINE += -D LOG_PRINT_EN #log记录时是否打印
endif
 
#软件版本
MAKE_DEFINE += -D APP_VER=\"$(APP_VER)\"
 

#编译依赖操作系统现有库
PROJECT_LIB := -lpthread
 
APP_XJ:
	@echo "---------- Start Make APP1 ------"
	@echo "app1 Source file Preview:<"$(OBJS)" >Source File List End\n"
	$(CC) $(MAKE_DEFINE) $(CFLAG) -o $(TARGET) $(OBJS) $(LFLAG)
	cp $(TARGET) $(PROJECT_DIR)/objs/
	cp $(TARGET) /mnt/hgfs/share/
	@echo "---------- Make APP1 Finished ------"
 
clean:
	rm $(TARGET) -rf
