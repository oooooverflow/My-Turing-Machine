; 设计思路：
; 对于原来的字符串，若为空串，则接收。若不为空串，则从第二个位置开始逐一作为第二个W的起始位置，并比较拆分出来的两个字符串是否相等。
; 若相等则接收，若不相等则进行下一次划分。直到划分之后，前一段字符串的长度比后一段的字符串长度大，则拒绝该字符串。
; 具体状态介绍：
; 0是起始状态，若为空串则接受。pre是准备状态，原始字符串第二个位置作为后一个W的起始位置，并打上标识。location是定位找到下一个index作为后一个W的起始位置（已被打上标记），一旦找到，则进入复制阶段。
; cp是复制状态，从可能的后一个W的起始位置开始的后面所有字符串复制到第二条纸带上。mh是将第一二两条纸带的指针指向纸带头部。
; cmp是比较第一二两条纸带上的字符内容，若相同则接受，若w1的长度大于w2的长度则拒绝输入，否则进入回退阶段。
; reduction是回退状态，负责把刚刚打上标记作为可能的第二个W起始点的标记擦除，并标记紧接着的后一个位置为可能的第二个W的起始位置，打上标记；并且清空第二条纸带的内容，为重新定位做准备。
; reject是清空第一条纸带的内容并填上False。accept是清空第一条纸带的内容并填上True。
; halt_reject是halt并拒绝输入。halt_accept是halt并接受输入。
#Q = {0,pre,location,cp,mh,cmp,reduction,reduction1,reduction2,accept,accept0,accept1,accept2,accept3,accept4,reject,reject0,reject1,reject2,reject3,reject4,reject5}

#S = {0,1}

#G = {0,1,_,T,r,u,e,F,a,l,s}

#q0 = 0

#B = _

#F = {accept}

#N = 3

; the transition functions
0 ___ *** *** accept
0 *__ *** r*r pre

; pre
pre *__ **X *** location

; location
location *_X *** *** cp
location *__ *** r*r location

; cp
cp 0_* 00* rrr cp
cp 1_* 11* rrr cp
cp __* *** lll mh

; mh
mh *** *** lll mh
mh _*_ *** *l* mh
mh 0_* *** l*l mh
mh 1_* *** l*l mh
mh ___ *** rrr cmp

; cmp
cmp 00_ *** rrr cmp
cmp 11_ *** rrr cmp
cmp 10_ *** *** reduction
cmp 01_ *** *** reduction
cmp **X *** *** reduction
cmp *_X *** *** accept
cmp *__ *** *** reject

; reduction
reduction **X **_ r*r reduction1
reduction1 **_ **X r*r reduction
reduction *** *** rrr reduction
reduction _*_ *** *r* reduction
reduction *_* *** r_r reduction
reduction ___ *** lll reduction2
reduction2 *** *_* lll reduction2
reduction2 _*_ *_* *l* reduction2
reduction2 *_* *** l*l reduction2
reduction2 ___ *** rrr location

; reject
reject *** *** rrr reject
reject ___ *** lll reject0
reject0 *** ___ lll reject0
reject0 ___ ___ r** reject1
reject1 ___ F__ r** reject2
reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject

; accept
accept *** *** rrr accept
accept ___ *** lll accept0
accept0 *** ___ lll accept0
accept0 ___ ___ r** accept1
accept1 ___ T__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept