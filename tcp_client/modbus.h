#pragma once
#include "modbus.h"

#include<iostream>
using namespace std;

//modbus功能码
#define CODE_BOOL_READ		(0x01)			 /*BOOL 读功能码 */
#define CODE_BOOL_WRITE		(0x05)/*(0x0F)*/ /*BOOL 写功能码 */
#define CODE_INT_READ		(0x03)			 /*INT  读功能码 */
#define CODE_INT_WRITE		(0x10)			 /*INT  写功能码 */
#define CODE_REAL_READ		CODE_INT_READ	 /*REAL 读功能码 */
#define CODE_REAL_WRITE		CODE_INT_WRITE   /*REAL 写功能码 */

class Modbus_data
{   
public:
    void read_coil();         //modbus读线圈

//数据属性
    uint16_t data;
};
