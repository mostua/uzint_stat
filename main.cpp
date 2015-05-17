#include "ext2_fs.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

const int BOOT_BLOCK_SIZE = 1024;

char buffer[1024];

int main()
{
	ext2_super_block sb;
	ext2_inode in;
    ifstream partition("ext2_part", ifstream::binary);
    partition.seekg(BOOT_BLOCK_SIZE);
    partition.read(buffer, sizeof(sb));
    memcpy (&sb, buffer, sizeof(sb));
    cout << sb.s_blocks_count << endl;
    cout << sb.s_free_blocks_count << endl;
    cout << sb.s_r_blocks_count << endl;
}
