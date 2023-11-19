# -*- coding: utf-8 -*-

import os,sys

JAVA_HOME_PATH = "C:\Program Files\Java\jdk1.8.0_101"

SPARK_HOME_PATH = "D:\apps\spark-2.0.1-bin-hadoop2.7"
HADOOP_HOME_PATH = "D:\apps\winutils\hadoop-3.2.0"

os.environ['JAVA_HOME'] = JAVA_HOME_PATH
os.environ['SPARK_HOME'] = SPARK_HOME_PATH
os.environ['HADOOP_HOME'] = HADOOP_HOME_PATH

if not JAVA_HOME_PATH in sys.path:
    sys.path.append(JAVA_HOME_PATH)
    
if not SPARK_HOME_PATH in sys.path:
    sys.path.append(SPARK_HOME_PATH)
if not HADOOP_HOME_PATH in sys.path:
    sys.path.append(HADOOP_HOME_PATH)
    
#os.environ['PYTHONPATH'] = 'D:\apps\anconda3'
from pyspark import SparkConf, SparkContext
# 创建SparkConf和SparkContext
#conf = SparkConf().setMaster("local").setAppName("lichao-wordcount")
conf = SparkConf()
sc = SparkContext(conf=conf)
# 输入的数据
data = ["hello", "world", "hello", "word", "count", "count", "hello"]
# 将Collection的data转化为spark中的rdd并进行操作
rdd = sc.parallelize(data)
resultRdd = rdd.map(lambda word: (word, 1)).reduceByKey(lambda a, b: a + b)
# rdd转为collecton并打印
resultColl = resultRdd.collect()
for line in resultColl:
    print(line)
    

"""    
import sys
import os
from pathlib import WindowsPath

SPARK_HOME_PATH = "D:\apps\spark-2.0.1-bin-hadoop2.7"
HADOOP_HOME_PATH = "D:\apps\winutils\hadoop-3.2.0"
os.environ['SPARK_HOME'] = SPARK_HOME_PATH
os.environ['HADOOP_HOME'] = HADOOP_HOME_PATH
if not SPARK_HOME_PATH in sys.path:
    sys.path.append(SPARK_HOME_PATH)
if not HADOOP_HOME_PATH in sys.path:
    sys.path.append(HADOOP_HOME_PATH)


#import findspark 
#findspark.init() 
import pyspark # only run after findspark.init() 
from pyspark.sql import SparkSession 
spark = SparkSession.builder.getOrCreate()  
df = spark.sql('''select 'spark' as hello ''') 
df.show()    

"""