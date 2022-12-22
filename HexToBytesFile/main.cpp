#include<iostream>
#include<fstream>


#define MAX_READ_BYTE 16
#define UCHAR unsigned char
#define UPCHAR unsigned char *
#define uint unsigned int


static unsigned long long sizefilerow = 0;


//非MAX_READ_BYTE整除，写入数据
//Writebuff 写出数据
//nGetNum   读取到的字节数
//str       读取到的单字节
//i         当前写入第i个字节
//pFileRead 读文件的句柄，判断是否到尾部
int superabundantWrite(UPCHAR Writebuff, size_t& nGetNum, UPCHAR str, uint& i, FILE* pFileRead)
{
    if (feof(pFileRead) && i == nGetNum - 1)
        sprintf_s(reinterpret_cast<char* const>(Writebuff), 8, "0x%X", *str);
    else
        sprintf_s(reinterpret_cast<char* const>(Writebuff), 8, "0x%X, ", *str);
    return 0;
}

//MAX_READ_BYTE整除，写入数据
//Writebuff 写出数据
//nGetNum   读取到的字节数
//str       读取到的单字节
//i         当前写入第i个字节
//pFileRead 读文件的句柄，判断是否到尾部
int divisibility(UPCHAR Writebuff, size_t& nGetNum, UPCHAR str, uint& i, FILE* pFileRead = NULL)
{
    if (!sizefilerow && i == nGetNum - 1)
        sprintf_s(reinterpret_cast<char* const>(Writebuff), 8, "0x%X", *str);
    else
        sprintf_s(reinterpret_cast<char* const>(Writebuff), 8, "0x%X, ", *str);
    return 0;
}






int main(int argv, char** args) {

    if (argv != 2)
        return argv;
    //读文件句柄，需要转换数组的文件
    FILE* pFileRead;
    //写出数组文件，句柄
    std::fstream pFileWrite;
    printf_s("二进制文件转十六进制数组工具开始生效：\n");

    printf_s("转换文件为：%s", args[1]);

    //打开读入文件，读取二进制文件
    if (fopen_s(&pFileRead, args[1], "rb"))
    {
        std::cout << "打开文件失败！！！" << std::endl;
        return argv;
    }

    //偏移文件句柄到文件尾
    _fseeki64(pFileRead, 0, SEEK_END);
    //获取文件大小
    unsigned long long sizeFile = _ftelli64(pFileRead);
    printf_s("转换文件大小为：%llu字节\n", sizeFile);

    //恢复文件句柄到文件首
    _fseeki64(pFileRead, 0, SEEK_SET);

    char NewFile[_MAX_PATH]{ 0 };
    sprintf_s(NewFile, _MAX_PATH, "%s.txt", args[1]);
    printf_s("输出文件为:%s\n", NewFile);

    //二进制打开写出文件
    pFileWrite.open(NewFile, std::ios::out | std::ios::trunc | std::ios::binary);
    //fopen_s(&pFileWite, NewFile, "wb");

    unsigned char Readbuff[18]{ 0 };
    unsigned char Writebuff[8]{ 0 };

    //判断文件大小是否可以整除MAX_READ_BYTE
    auto sizeFlag = sizeFile % MAX_READ_BYTE;
    if (!sizeFlag) {
        //如果文件整除16，获取文件有多少row
        sizefilerow = sizeFile / MAX_READ_BYTE;
    }

    //循环读取、写入数据
    while (true)
    {
        if (!sizeFlag)
            sizefilerow--;
        
        //每次读出16字节数据
        auto nGetNum = fread_s(Readbuff, sizeof(Readbuff), 1, MAX_READ_BYTE, pFileRead);
        auto str = Readbuff;
        for (uint i = 0, nWrite = 0; i < nGetNum; str++, i++)
        {
            if (sizeFlag)
                superabundantWrite(Writebuff, nGetNum, str, i, pFileRead);
            else
                divisibility(Writebuff, nGetNum, str, i);

            //将格式化的数据写入到数组文件
            pFileWrite << Writebuff;
            //fwrite(Writebuff, nWrite, 1, pFileWite);
        }

        if (!feof(pFileRead))
        {
            pFileWrite << "\r";
            //fwrite("\r", sizeof("\r"), 1, pFileWite);
        }
        else
            break;
    }

    //关闭文件句柄
    fclose(pFileRead);
    pFileWrite.close();
    //fclose(pFileWite);
    printf_s("二进制文件转十六进制数组工具执行完毕！\n");
    return argv;
}