#include<iostream>
#include<fstream>


#define MAX_READ_BYTE 16


int main(int argv, char** args) {

    if (argv != 2)
        return argv;
    FILE* pFileRead;
    std::fstream pFileWrite;
    printf_s("二进制文件转十六进制数组工具开始生效：\n");

    printf_s("转换文件为：%s\n", args[1]);
    fopen_s(&pFileRead, args[1], "rb");

    char NewFile[_MAX_PATH]{ 0 };
    sprintf_s(NewFile, _MAX_PATH, "%s.txt", args[1]);
    printf_s("输出文件为:%s\n", NewFile);

    pFileWrite.open(NewFile, std::ios::out | std::ios::trunc | std::ios::binary);
    //fopen_s(&pFileWite, NewFile, "wb");

    unsigned char Readbuff[18]{ 0 };
    unsigned char Writebuff[8]{ 0 };

    auto size = sizeof(Readbuff);
    while (true)
    {
        auto nGetNum = fread_s(Readbuff, sizeof(Readbuff), 1, MAX_READ_BYTE, pFileRead);
        auto str = Readbuff;
        for (unsigned int i = 0, nWrite = 0; i < nGetNum; str++, i++)
        {
           /* if (feof(pFileRead) && i == nGetNum - 1)
                nWrite = sprintf_s(reinterpret_cast<char* const>(Writebuff), sizeof(Writebuff), "0x%X", *str);
            else*/
                nWrite = sprintf_s(reinterpret_cast<char* const>(Writebuff), sizeof(Writebuff), "0x%X, ", *str);

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