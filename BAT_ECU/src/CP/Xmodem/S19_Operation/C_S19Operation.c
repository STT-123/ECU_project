#include "C_S19Operation.h"



int f_getc(FILE *fp)
{
    unsigned char c;
    size_t rc = fread(&c, 1, 1, fp);
    if (rc != 1)
    {
        return EOF;
    }
    return c;
}


int hexvalue(int c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'F') return c - 'A' + 10;
    if ('a' <= c && c <= 'f') return c - 'a' + 10;
    return -1;
}

// S19 转 BIN 文件转换函数
signed char S192BIN(const char *srec_file_path, const char *bin_file_path) {
    FILE *fp_srec = NULL;
    FILE *fp_bin = NULL;

    int state = SREC_NEWLINE;
    int nibble = HI;
    int bytes = 0;
    int type = 0;
    int c, byte_value = 0, nibble_value = 0;
    int byte_count = 0, address = 0, value = 0;
    int addr_bytes = 0, data_bytes = 0;
    int checksum = 0, error = 0, processing = 1;
    unsigned char byte;

    if (srec_file_path == NULL || bin_file_path == NULL)
        return -1;

    fp_srec = fopen(srec_file_path, "r");
    if (!fp_srec) {
        printf("Failed to open SREC file: %s\n", srec_file_path);
        return -2;
    }

    fp_bin = fopen(bin_file_path, "wb");
    if (!fp_bin) {
        printf("Failed to open BIN file: %s\n", bin_file_path);
        fclose(fp_srec);
        return -3;
    }

    while (processing && (c = fgetc(fp_srec)) != EOF) {
        switch (state) {
            case SREC_NEWLINE:
                if (c == 'S' || c == 's') {
                    state = SREC_RECORDTYPE;
                }
                break;

            case SREC_RECORDTYPE:
                if (isdigit(c)) {
                    type = c - '0';
                    state = SREC_BYTECOUNT;
                    nibble = HI;
                    bytes = 1;
                    value = 0;
                    checksum = 0;
                } else {
                    processing = 0;
                    error = 1;
                }
                break;

            case SREC_BYTECOUNT:
                nibble_value = hexvalue(c);
                if (nibble_value >= 0) {
                    if (nibble == HI) {
                        nibble = LO;
                        byte_value = nibble_value;
                    } else {
                        nibble = HI;
                        byte_value = byte_value * 16 + nibble_value;
                        checksum += byte_value;
                        byte_count = byte_value;

                        switch (type) {
                            case 0: addr_bytes = 2; break;
                            case 1: addr_bytes = 2; break;
                            case 2: addr_bytes = 3; break;
                            case 3: addr_bytes = 4; break;
                            case 5: addr_bytes = 2; break;
                            case 7: addr_bytes = 4; break;
                            case 8: addr_bytes = 3; break;
                            case 9: addr_bytes = 2; break;
                            default:
                                processing = 0;
                                error = 1;
                                break;
                        }

                        data_bytes = byte_count - addr_bytes - 1;
                        value = 0;
                        bytes = addr_bytes;
                        state = (addr_bytes > 0) ? SREC_ADDRESS : SREC_DATA;
                    }
                } else {
                    processing = 0;
                    error = 1;
                }
                break;

            case SREC_ADDRESS:
                nibble_value = hexvalue(c);
                if (nibble_value >= 0) {
                    if (nibble == HI) {
                        nibble = LO;
                        byte_value = nibble_value;
                    } else {
                        nibble = HI;
                        byte_value = byte_value * 16 + nibble_value;
                        checksum += byte_value;
                        value = (value << 8) | byte_value;
                        bytes--;
                        if (bytes == 0) {
                            address = value;
                            bytes = data_bytes;
                            state = (bytes > 0) ? SREC_DATA : SREC_CHKSUM;
                        }
                    }
                } else {
                    processing = 0;
                    error = 1;
                }
                break;

            case SREC_DATA:
                nibble_value = hexvalue(c);
                if (nibble_value >= 0) {
                    if (nibble == HI) {
                        nibble = LO;
                        byte_value = nibble_value;
                    } else {
                        nibble = HI;
                        byte_value = byte_value * 16 + nibble_value;
                        checksum += byte_value;

                        if (type == 1 || type == 2 || type == 3) {
                            byte = byte_value;
                            fwrite(&byte, 1, 1, fp_bin);
                        }

                        bytes--;
                        if (bytes == 0) {
                            state = SREC_CHKSUM;
                            bytes = 1;
                        }
                    }
                } else {
                    processing = 0;
                    error = 1;
                }
                break;

            case SREC_CHKSUM:
                nibble_value = hexvalue(c);
                if (nibble_value >= 0) {
                    if (nibble == HI) {
                        nibble = LO;
                        byte_value = nibble_value;
                    } else {
                        nibble = HI;
                        byte_value = byte_value * 16 + nibble_value;
                        checksum += byte_value;
                        if ((checksum & 0xFF) != 0xFF) {
                            printf("Checksum mismatch!\n");
                        }
                        state = SREC_NEWLINE;
                    }
                } else {
                    processing = 0;
                    error = 1;
                }
                break;

            default:
                processing = 0;
                error = 1;
                break;
        }
    }

    fclose(fp_srec);
    fclose(fp_bin);
    return (error == 0) ? 0 : -4;
}
