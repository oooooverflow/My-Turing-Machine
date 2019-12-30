; 设计思路：
; 使用三条纸带，初始状态第二条和第三条纸带上只有一个0，在这两条纸带上模拟斐波那契数列的迭代过程。每次先分别比较第一条纸带上的0的个数，若第一条纸带上的0都是略多的一方，则继续进行斐波那契数列的迭代。
; 把第二条纸带上的0全都拼接到第三条纸带后面，再把第三条纸带上的内容拼接到第二条纸带的后面，这里进行了两步斐波那契数列的迭代，a(n+1) = a(n-1)+a(n)以及a(n+2) = a(n+1)+a(n)，然后继续比较0的个数。
; 直到后两条纸带上的0的个数与第一条纸带上的0个数相等，则accept打印True，或者第一条纸带上的0个数小于另两个或者介于两者之间则reject打印False。
; 具体状态介绍：
; 0是起始状态。p1是在第二条和第三条纸带上纸带上初始化一个0。jdg1pre是将纸带一和二的指针指向纸袋头部，准备比较0的个数。jdg1是比较第一个纸带和第二个纸带上的0的个数是否相等。
; jdg2pre是将第一个纸带和第三个纸带的指针指向纸带头部，准备比较0的个数。jdg2是比较第一个纸带和第三个纸带上的0的个数是否相等。
; mh1是将第二条纸带的指针指向纸带头部，准备复制。mh2是将第三条纸带的指针指向纸带头部，准备复制。
; cp1是将第二条纸带的内容拼接到第三条纸带的后面。cp2是将第三条纸带的内容拼接到第二条纸带的后面。
; reject是清空第一条纸带的内容并填上False。accept是清空第一条纸带的内容并填上True。
; halt_reject是halt并拒绝输入。halt_accept是halt并接受输入。
#Q = {0,p1,jdg1pre,jdg2pre,jdg1,jdg2,mh1,mh2,cp1,cp2,reject,reject0.reject1,reject2,reject3,reject4,halt_reject,accept,accept0,accept1,accept2,accept3,halt_accept}

#S = {0}

#G = {0,_,T,r,u,e,F,a,l,s}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 3

; Transition funtion

; 0
0 *_* *0* *** p1

; p1
p1 **_ **0 *** jdg1pre

; jdg1pre
jdg1pre 00* *** ll* jdg1pre
jdg1pre 0_* *** l** jdg1pre
jdg1pre _0* *** *l* jdg1pre
jdg1pre __* *** rr* jdg1

; jdg1
jdg1 00* *** rr* jdg1
jdg1 0_* *** *l* jdg2pre
jdg1 __* *** ll* accept
jdg1 _0* *** l** jdg2pre

; jdg2pre
jdg2pre 0*0 *** l*l jdg2pre
jdg2pre 0*_ *** l** jdg2pre
jdg2pre _*0 *** **l jdg2pre
jdg2pre _*_ *** r*r jdg2

; jdg2
jdg2 0*0 *** r*r jdg2
jdg2 0*_ *** **l mh1
jdg2 _*_ *** l*l accept
jdg2 _*0 *** l** reject

; mh1
mh1 *0* *** *l* mh1
mh1 *_* *** *r* cp1

; mh2
mh2 **0 *** **l mh2
mh2 **_ *** **r cp2

; cp1
cp1 *00 *** **r cp1
cp1 *0_ **0 *rr cp1
cp1 *__ *** *ll mh2

; cp2
cp2 *00 *** *r* cp2
cp2 *_0 *0* *rr cp2
cp2 *__ *** *ll jdg1pre

; reject
reject *00 *** *rr reject
reject *0_ *** *r* reject
reject *_0 *** **r reject
reject *__ *** *ll reject0
reject0 *** ___ lll reject0
reject0 ___ F__ r** reject1
reject1 ___ a__ r** reject2
reject2 ___ l__ r** reject3
reject3 ___ s__ r** reject4
reject4 ___ e__ *** halt_reject

; accept
accept *00 *** *rr accept
accept *0_ *** *r* accept
accept *_0 *** **r accept
accept *__ *** *ll accept0
accept0 *** ___ lll accept0
accept0 ___ T__ r** accept1
accept1 ___ r__ r** accept2
accept2 ___ u__ r** accept3
accept3 ___ e__ *** halt_accept
