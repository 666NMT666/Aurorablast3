#ifndef _COMP_CPP
#define _COMP_CPP
#include "comp.h"
void do_decompress(const char* const in_file, const char* const out_file){
        char inbuf[INBUFSIZ];           // 入力バッファ
        char outbuf[OUTBUFSIZ];         // 出力バッファ
        char err_msg[250];
        FILE *fin, *fout;       // 入力・出力ファイル
		errno_t err;
        int count, status;
        z_stream z;             // ライブラリとやりとりするための構造体
        if ((err = fopen_s(&fin, in_file, "rb"))!=0) return;
        if ((err = fopen_s(&fout, out_file, "wb")) != 0) return;

        // すべてのメモリ管理をライブラリに任せる
        z.zalloc = Z_NULL;
        z.zfree = Z_NULL;
        z.opaque = Z_NULL;

        // 初期化
        z.next_in = Z_NULL;
        z.avail_in = 0;
        if (inflateInit(&z) != Z_OK) {
                sprintf_s(err_msg, "展開初期化エラー（inflateInit関数）: %s\n", (z.msg) ? z.msg : "???");
                MessageBox(NULL, err_msg, in_file, MB_OK);
                fclose(fin);
                fclose(fout);
                return;
        }

        z.next_out = (Bytef*)outbuf;            // 出力ポインタ
        z.avail_out = OUTBUFSIZ;        // 出力バッファ残量
        status = Z_OK;

        while (status != Z_STREAM_END) {
                if (z.avail_in == 0) {  // 入力残量がゼロになれば
                        z.next_in = (Bytef*)inbuf;      // 入力ポインタを元に戻す
                        z.avail_in = fread(inbuf, 1, INBUFSIZ, fin); // データを読む
                }
                status = inflate(&z, Z_NO_FLUSH); // 展開
                if (status == Z_STREAM_END) break; // 完了
                if (status != Z_OK) {   // エラー
                        sprintf_s(err_msg, "展開エラー（inflate関数）: %s\n", (z.msg) ? z.msg : "???");
                        MessageBox(NULL, err_msg,in_file, MB_OK);
                        fclose(fin);
                        fclose(fout);
                        return;
                }
                if (z.avail_out == 0) { // 出力バッファが尽きれば まとめて書き出す
                        if (fwrite(outbuf, 1, OUTBUFSIZ, fout) != OUTBUFSIZ) {
                                MessageBox(NULL, "書込エラー（fwrite関数）\n",in_file, MB_OK);
                                fclose(fin);
                                fclose(fout);
                                return;
                        }
                        z.next_out = (Bytef*)outbuf; // 出力ポインタを元に戻す
                        z.avail_out = OUTBUFSIZ; // 出力バッファ残量を元に戻す
                }
        }

        // 残りを吐き出す
        if ((count = OUTBUFSIZ - z.avail_out) != 0) {
                if (fwrite(outbuf, 1, count, fout) != count) {
                        MessageBox(NULL, "書込エラー（fwrite関数）\n",in_file, MB_OK);
                        fclose(fin);
                        fclose(fout);
                        return;
                }
        }

        // 後始末
        if (inflateEnd(&z) != Z_OK) {
                sprintf_s(err_msg, "展開終了エラー（inflateEnd関数）: %s\n", (z.msg) ? z.msg : "???");
                MessageBox(NULL, err_msg, in_file, MB_OK);
                fclose(fin);
                fclose(fout);
                return;
        }
        fclose(fin);
        fclose(fout);
        return;
}

#endif