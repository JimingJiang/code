# -*- coding: utf-8 -*-
#author: GeekSword
#site: http://onestraw.net

ring={1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0}



def show_operation(num,flag):
    if flag == 0:
        print(u"%d号环 上" %num)
    elif flag == 1:
        print(u"%d号环 下" %num)
    else:
        print(u"flag error")

def operate_ring(ring_num, flag):
    if ring_num == 1:
        if ring[ring_num] != flag:
            ring[ring_num] = flag
            show_operation(ring_num, flag)
            return 1
        else:
            return 0
    elif ring_num <= 9 and ring_num >1:

        if ring[ring_num] != flag:
            n = 0
            n += operate_ring(ring_num - 1,0)
            rno = ring_num - 2
            while rno > 0 and ring[rno] == 0:
                n += operate_ring(rno, 1)
                rno -= 1
            ring[ring_num] = flag
            show_operation(ring_num, flag)
            n += 1
            return n
        else:
            return 0
    else:
        return 0

def move_ring(num):
    for k in ring.keys():
        ring[k]=0
    k = num
    count = 0
    
    while k>0:
        count += operate_ring(k,1)
        k -= 1
    print(u"解%d连环至少需要%d步" %(num, count))
    
if __name__ =='__main__':
    print(u"本程序对九连环上的环进行编号，1表示最外面的环(最易解下的)，9表示最里面的环(最难解下的)")
    move_ring(9)
