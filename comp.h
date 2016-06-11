#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "zlib.h"

#define INBUFSIZ   4096                 // 入力バッファサイズ（任意）
#define OUTBUFSIZ  4096                 // 出力バッファサイズ（任意）

// 展開（復元）
void do_decompress(const char* const in_file,const char* const out_file);

//do_decompress(s2, s1);
  