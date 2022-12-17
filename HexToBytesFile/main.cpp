#include<iostream>
#include<fstream>


#define MAX_READ_BYTE 16
#define UCHAR unsigned char
#define UPCHAR unsigned char *
#define uint unsigned int


static unsigned long long sizefilerow = 0;


//非MAX_READ_BYTE整除，写入数据
int superabundantWrite(UPCHAR Writebuff, size_t& nGetNum, UPCHAR str, uint& i, FILE* pFileRead)
{
    if (feof(pFileRead) && i == nGetNum - 1)
        sprintf_s(reinterpret_cast<char* const>(Writebuff), 8, "0x%X", *str);
    else
        sprintf_s(reinterpret_cast<char* const>(Writebuff), 8, "0x%X, ", *str);
    return 0;
}

//MAX_READ_BYTE整除，写入数据
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
    FILE* pFileRead;
    std::fstream pFileWrite;
    printf_s("二进制文件转十六进制数组工具开始生效：\n");

    printf_s("转换文件为：%s", args[1]);
    if (fopen_s(&pFileRead, args[1], "rb"))
    {
        std::cout << "打开文件失败！！！" << std::endl;
        return argv;
    }

    _fseeki64(pFileRead, 0, SEEK_END);
    unsigned long long sizeFile = _ftelli64(pFileRead);
    printf_s("转换文件大小为：%lluKB\n", sizeFile / 1024);
    _fseeki64(pFileRead, 0, SEEK_SET);

    char NewFile[_MAX_PATH]{ 0 };
    sprintf_s(NewFile, _MAX_PATH, "%s.txt", args[1]);
    printf_s("输出文件为:%s\n", NewFile);

    pFileWrite.open(NewFile, std::ios::out | std::ios::trunc | std::ios::binary);
    //fopen_s(&pFileWite, NewFile, "wb");

    unsigned char Readbuff[18]{ 0 };
    unsigned char Writebuff[8]{ 0 };

    auto sizeFlag = sizeFile % MAX_READ_BYTE;
    if (!sizeFlag) {
        sizefilerow = sizeFile / MAX_READ_BYTE;
    }

    while (true)
    {
        if (!sizeFlag)
            sizefilerow--;
        auto nGetNum = fread_s(Readbuff, sizeof(Readbuff), 1, MAX_READ_BYTE, pFileRead);
        auto str = Readbuff;
        for (uint i = 0, nWrite = 0; i < nGetNum; str++, i++)
        {
            if (sizeFlag)
                superabundantWrite(Writebuff, nGetNum, str, i, pFileRead);
            divisibility(Writebuff, nGetNum, str, i);
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

    fclose(pFileRead);
    pFileWrite.close();
    //fclose(pFileWite);
    printf_s("二进制文件转十六进制数组工具执行完毕！\n");
    return argv;
}