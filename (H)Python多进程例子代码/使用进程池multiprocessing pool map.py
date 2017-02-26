#coding: utf-8
import multiprocessing 

def m1(x): 
    print x * x 

if __name__ == '__main__': 
    pool = multiprocessing.Pool(multiprocessing.cpu_count()) 
    i_list = range(8)
    pool.map(m1, i_list)