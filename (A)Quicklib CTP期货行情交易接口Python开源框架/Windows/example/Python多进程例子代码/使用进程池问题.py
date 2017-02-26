'''
大家接触到python多进程的一个典型的例子如下，程序执行起来也没有任何问题。
import multiprocessing

def f(x):
    return x*x

def go():
    pool = multiprocessing.Pool(processes=4)            
    #result = pool.apply_async(self.f, [10])     
    #print result.get(timeout=1)           
    print pool.map(f, range(10))


if __name__== '__main__' :
    go()
可是，一旦加入了class，程序就显示错误。程序和结果如下：
程序：
import multiprocessing

class someClass(object):
    def __init__(self):
        pass

    def f(self, x):
        return x*x

    def go(self):
        pool = multiprocessing.Pool(processes=4)            
        #result = pool.apply_async(self.f, [10])     
        #print result.get(timeout=1)           
        print pool.map(self.f, range(10))

结果：
PicklingError: Can't pickle <type 'instancemethod'>: attribute lookup __builtin__.instancemethod failed
请问有什么解决方法？
谢谢


'''

#coding: utf-8
import multiprocessing
import logging

def create_logger(i):
    print i

class CreateLogger(object):
    def __init__(self, func):
        self.func = func

if __name__ == '__main__':
    ilist = range(10)

    cl = CreateLogger(create_logger)
    pool = multiprocessing.Pool(multiprocessing.cpu_count())
    pool.map(cl.func, ilist)

    print "hello------------>"