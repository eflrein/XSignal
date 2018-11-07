# XSignal

## Description
一个信号槽机制的实现<br>
XSignal相较于前一版(signal-slot)进行了简化，并增加了功能

## Details
* XSignal中的Connection对象仅可移动，不可复制，保证Connection对象的唯一性
* XSignal中可以获取任意Slot函数的返回值，通过Connection对象的value()方法
* XSignal不提供Connection有效性检查接口，在disconnect()之后，请不要调用value方法
* 不论是老版本的signal-slot还是现在的XSignal，Connection对象析构都不会导致Slot函数被删除，仅有在Signal对象析构或主动disconnect()时才会删除Slot函数
