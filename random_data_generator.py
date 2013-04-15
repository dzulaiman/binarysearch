#!/usr/bin/env python
#Random intial data for binary tree
#Output: %d %s %d
#Given initial
#dzul.aiman@gmail.com

import random

def random_int(sizesample):

    unique = []
    maximum = sizesample
    minimum = 1
    
    while(minimum<maximum+1):
        y = random.randrange(1,maximum+1)
        if y not in unique:
            unique.append(y)
            #Uncomment below to debug output x and y
            #print "x :", minimum, "y :", y
            minimum = minimum + 1

    return unique

def random_name(sizesamp):
    namefile = open("100names.txt")
    nameread = namefile.readlines()
    return random.sample(nameread,sizesamp)
    

def random_phone():
    phone = ['1','2','3','4','5','6','7','8','9','0']
    #tel = [0,1] + phone
    tel = ''.join(random.sample(phone,7))
    return "01" + tel
        

if __name__ == "__main__":

    print "Generate random sample for node and names\n"
    
    sample = raw_input("How many samples to generate : ")
    sample = int(sample)
    
    number = random_int(sample)
    names = random_name(sample)

    fileout = open("phonebook_rand_100.txt","aw")

    for num,name in zip(number,names):
        num = str(num)
        name = name.strip("\n")
        phonenum = random_phone()
        outstring =  num + " " + name + " " + phonenum
        fileout.write(outstring)
        fileout.write("\n")
    fileout.close()
    print "Output to file: phonebook_rand_100.txt"
    
    

    
