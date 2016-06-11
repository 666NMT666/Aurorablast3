#ifndef _COMP_CPP
#define _COMP_CPP
#include "comp.h"
void do_decompress(const char* const in_file, const char* const out_file){
        char inbuf[INBUFSIZ];           // ���̓o�b�t�@
        char outbuf[OUTBUFSIZ];         // �o�̓o�b�t�@
        char err_msg[250];
        FILE *fin, *fout;       // ���́E�o�̓t�@�C��
		errno_t err;
        int count, status;
        z_stream z;             // ���C�u�����Ƃ��Ƃ肷�邽�߂̍\����
        if ((err = fopen_s(&fin, in_file, "rb"))!=0) return;
        if ((err = fopen_s(&fout, out_file, "wb")) != 0) return;

        // ���ׂẴ������Ǘ������C�u�����ɔC����
        z.zalloc = Z_NULL;
        z.zfree = Z_NULL;
        z.opaque = Z_NULL;

        // ������
        z.next_in = Z_NULL;
        z.avail_in = 0;
        if (inflateInit(&z) != Z_OK) {
                sprintf_s(err_msg, "�W�J�������G���[�iinflateInit�֐��j: %s\n", (z.msg) ? z.msg : "???");
                MessageBox(NULL, err_msg, in_file, MB_OK);
                fclose(fin);
                fclose(fout);
                return;
        }

        z.next_out = (Bytef*)outbuf;            // �o�̓|�C���^
        z.avail_out = OUTBUFSIZ;        // �o�̓o�b�t�@�c��
        status = Z_OK;

        while (status != Z_STREAM_END) {
                if (z.avail_in == 0) {  // ���͎c�ʂ��[���ɂȂ��
                        z.next_in = (Bytef*)inbuf;      // ���̓|�C���^�����ɖ߂�
                        z.avail_in = fread(inbuf, 1, INBUFSIZ, fin); // �f�[�^��ǂ�
                }
                status = inflate(&z, Z_NO_FLUSH); // �W�J
                if (status == Z_STREAM_END) break; // ����
                if (status != Z_OK) {   // �G���[
                        sprintf_s(err_msg, "�W�J�G���[�iinflate�֐��j: %s\n", (z.msg) ? z.msg : "???");
                        MessageBox(NULL, err_msg,in_file, MB_OK);
                        fclose(fin);
                        fclose(fout);
                        return;
                }
                if (z.avail_out == 0) { // �o�̓o�b�t�@���s����� �܂Ƃ߂ď����o��
                        if (fwrite(outbuf, 1, OUTBUFSIZ, fout) != OUTBUFSIZ) {
                                MessageBox(NULL, "�����G���[�ifwrite�֐��j\n",in_file, MB_OK);
                                fclose(fin);
                                fclose(fout);
                                return;
                        }
                        z.next_out = (Bytef*)outbuf; // �o�̓|�C���^�����ɖ߂�
                        z.avail_out = OUTBUFSIZ; // �o�̓o�b�t�@�c�ʂ����ɖ߂�
                }
        }

        // �c���f���o��
        if ((count = OUTBUFSIZ - z.avail_out) != 0) {
                if (fwrite(outbuf, 1, count, fout) != count) {
                        MessageBox(NULL, "�����G���[�ifwrite�֐��j\n",in_file, MB_OK);
                        fclose(fin);
                        fclose(fout);
                        return;
                }
        }

        // ��n��
        if (inflateEnd(&z) != Z_OK) {
                sprintf_s(err_msg, "�W�J�I���G���[�iinflateEnd�֐��j: %s\n", (z.msg) ? z.msg : "???");
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