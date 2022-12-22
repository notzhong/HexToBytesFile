#include<iostream>
#include<fstream>


#define MAX_READ_BYTE 16
#define UCHAR unsigned char
#define UPCHAR unsigned char *
#define uint unsigned int


static unsigned long long sizefilerow = 0;


//��MAX_READ_BYTE������д������
//Writebuff д������
//nGetNum   ��ȡ�����ֽ���
//str       ��ȡ���ĵ��ֽ�
//i         ��ǰд���i���ֽ�
//pFileRead ���ļ��ľ�����ж��Ƿ�β��
int superabundantWrite(UPCHAR Writebuff, size_t& nGetNum, UPCHAR str, uint& i, FILE* pFileRead)
{
    if (feof(pFileRead) && i == nGetNum - 1)
        sprintf_s(reinterpret_cast<char* const>(Writebuff), 8, "0x%X", *str);
    else
        sprintf_s(reinterpret_cast<char* const>(Writebuff), 8, "0x%X, ", *str);
    return 0;
}

//MAX_READ_BYTE������д������
//Writebuff д������
//nGetNum   ��ȡ�����ֽ���
//str       ��ȡ���ĵ��ֽ�
//i         ��ǰд���i���ֽ�
//pFileRead ���ļ��ľ�����ж��Ƿ�β��
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
    //���ļ��������Ҫת��������ļ�
    FILE* pFileRead;
    //д�������ļ������
    std::fstream pFileWrite;
    printf_s("�������ļ�תʮ���������鹤�߿�ʼ��Ч��\n");

    printf_s("ת���ļ�Ϊ��%s", args[1]);

    //�򿪶����ļ�����ȡ�������ļ�
    if (fopen_s(&pFileRead, args[1], "rb"))
    {
        std::cout << "���ļ�ʧ�ܣ�����" << std::endl;
        return argv;
    }

    //ƫ���ļ�������ļ�β
    _fseeki64(pFileRead, 0, SEEK_END);
    //��ȡ�ļ���С
    unsigned long long sizeFile = _ftelli64(pFileRead);
    printf_s("ת���ļ���СΪ��%llu�ֽ�\n", sizeFile);

    //�ָ��ļ�������ļ���
    _fseeki64(pFileRead, 0, SEEK_SET);

    char NewFile[_MAX_PATH]{ 0 };
    sprintf_s(NewFile, _MAX_PATH, "%s.txt", args[1]);
    printf_s("����ļ�Ϊ:%s\n", NewFile);

    //�����ƴ�д���ļ�
    pFileWrite.open(NewFile, std::ios::out | std::ios::trunc | std::ios::binary);
    //fopen_s(&pFileWite, NewFile, "wb");

    unsigned char Readbuff[18]{ 0 };
    unsigned char Writebuff[8]{ 0 };

    //�ж��ļ���С�Ƿ��������MAX_READ_BYTE
    auto sizeFlag = sizeFile % MAX_READ_BYTE;
    if (!sizeFlag) {
        //����ļ�����16����ȡ�ļ��ж���row
        sizefilerow = sizeFile / MAX_READ_BYTE;
    }

    //ѭ����ȡ��д������
    while (true)
    {
        if (!sizeFlag)
            sizefilerow--;
        
        //ÿ�ζ���16�ֽ�����
        auto nGetNum = fread_s(Readbuff, sizeof(Readbuff), 1, MAX_READ_BYTE, pFileRead);
        auto str = Readbuff;
        for (uint i = 0, nWrite = 0; i < nGetNum; str++, i++)
        {
            if (sizeFlag)
                superabundantWrite(Writebuff, nGetNum, str, i, pFileRead);
            else
                divisibility(Writebuff, nGetNum, str, i);

            //����ʽ��������д�뵽�����ļ�
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

    //�ر��ļ����
    fclose(pFileRead);
    pFileWrite.close();
    //fclose(pFileWite);
    printf_s("�������ļ�תʮ���������鹤��ִ����ϣ�\n");
    return argv;
}