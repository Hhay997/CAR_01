#include "spi_01.h"
#include "spi.h"


/** 硬件SPI */
#define SPI_WAIT_TIMEOUT			((uint16_t)0xFFFF)
/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:接收到的字节
  */
unsigned char drv_spi_read_write_byte( unsigned char * TxByte)
{
	uint8_t l_Data = 0;
	uint16_t l_WaitTime = 0;

	while(  SPI_FLAG_TXE==0)		//等待发送缓冲区为空
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//如果等待超时则退出
		}
	}
	l_WaitTime = SPI_WAIT_TIMEOUT / 2;		//重新设置接收等待时间(因为SPI的速度很快，正常情况下在发送完成之后会立即收到数据，等待时间不需要过长)
	HAL_SPI_Transmit(&hspi1,TxByte,1,1000);//发送数据

	while(  HAL_SPI_GetState(&hspi1)==1)		//等待接收缓冲区非空
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//如果等待超时则退出
		}
	}

	HAL_SPI_Receive(&hspi1,TxByte,10,1000);	//读取接收数据

	return l_Data;		//返回
}

/**
  * @brief :SPI收发字符串
  * @param :
  *			@ReadBuffer: 接收数据缓冲区地址
  *			@WriteBuffer:发送字节缓冲区地址
  *			@Length:字节长度
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:无
  */
void drv_spi_read_write_string( unsigned char* ReadBuffer, unsigned char* WriteBuffer, int Length )
{
	HAL_GPIO_WritePin(SPI1_CE_GPIO_Port,SPI1_CE_Pin,1);

	while( Length-- )
	{
		//ReadBuffer = drv_spi_read_write_byte(WriteBuffer);		//收发数据
		ReadBuffer++;
		WriteBuffer++;				//读写地址加1
	}
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port,SPI1_NSS_Pin,1);			//拉高片选
}

/** 硬件SPI */

/*
unsigned char SPI1_ReadWriteByte(unsigned char *TxData)
{
    u8 retry=0;
    while (SPI_FLAG_TXE== 0) //检查发送缓存空标志位设置与否
        {
        retry++;
        if(retry>200)return 0;
        }
    HAL_SPI_Receive(&SPI1, TxData,1,0xff); //通过外设SPI1发送一个数据
    retry=0;

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//检查接受缓存非空标志位设置与否
        {
        retry++;
        if(retry>200)return 0;
        }
    return SPI_I2S_ReceiveData(SPI1); //返回通过SPI1最近接收的数据*/
