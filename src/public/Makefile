#需要生成静态库的Makefile
#程序根目录
top_srcdir	= ..

#生成静态库后所存放的位置
libdir = $(top_srcdir)/lib
#静态库文件名
LIBNAME		= libfa_public.a
#路径+静态库文件名
TARGET		= $(libdir)/$(LIBNAME)

CPP_FILES = $(shell ls *.cpp)
C_FILES = $(-shell ls *.c)
SRCS = $(CPP_FILES) $(C_FILES)
BASE = $(basename $(SRCS))
OBJS = $(addsuffix .o, $(addprefix obj/,$(BASE)))
DEPS = $(addsuffix .d, $(addprefix dep/,$(BASE)))

#包含公共Make规则
include $(top_srcdir)/makeinclude/Make.rules

#设置头文件及库文件的位置
INCLUDEDIR := $(INCLUDEDIR)

$(TARGET): $(OBJS)
	-rm -f $@
	ar cr $(TARGET) $(OBJS)