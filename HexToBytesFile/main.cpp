#include<iostream>

int main(int argv, char** args) {

    if (argv != 2)
        return argv;
    FILE* pFileRead, * pFileWite;
    printf_s("�������ļ�תʮ���������鹤�߿�ʼ��Ч��\n");

    printf_s("ת���ļ�Ϊ��%s\n", args[1]);
    fopen_s(&pFileRead, args[1], "rb");

    char NewFile[_MAX_PATH]{ 0 };
    sprintf_s(NewFile, _MAX_PATH, "%s.txt", args[1]);
    printf_s("����ļ�Ϊ:%s\n", NewFile);
    fopen_s(&pFileWite, NewFile, "w");

    unsigned char Readbuff[17]{ 0 };
    unsigned char Writebuff[8]{ 0 };

    auto size = sizeof(Readbuff);
    while (true)
    {
        auto GetNum = fread_s(Readbuff, sizeof(Readbuff), 1, 16, pFileRead);
        auto str = Readbuff;
        for (unsigned int i = 0; i < GetNum; str++, i++)
        {
            auto nWrite = sprintf_s(reinterpret_cast<char* const>(Writebuff), sizeof(Writebuff), "0x%X, ", *str);

            fwrite(Writebuff, nWrite, 1, pFileWite);
        }
        if (!feof(pFileRead))
            fwrite("\r", sizeof("\r"), 1, pFileWite);
        else
            break;
    }

    fclose(pFileRead);
    fclose(pFileWite);
    printf_s("�������ļ�תʮ���������鹤��ִ����ϣ�\n");
    return argv;
}