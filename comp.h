#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "zlib.h"

#define INBUFSIZ   4096                 // ���̓o�b�t�@�T�C�Y�i�C�Ӂj
#define OUTBUFSIZ  4096                 // �o�̓o�b�t�@�T�C�Y�i�C�Ӂj

// �W�J�i�����j
void do_decompress(const char* const in_file,const char* const out_file);

//do_decompress(s2, s1);
  