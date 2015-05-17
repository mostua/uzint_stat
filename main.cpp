#include "ext2_defs/super_block.h"
#include "ext2_defs/inode.h"
#include "ext2_defs/block_group.h"
#include "ext2_defs/block_group.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

const int BOOT_BLOCK_SIZE = 1024;

char buffer[1024];

int main()
{
	super_block sb;
	inode in;
	block_group bg;

    ifstream partition("ext2_part", ifstream::binary);
    partition.seekg(BOOT_BLOCK_SIZE);
    partition.read(buffer, sizeof(sb));
    memcpy (&sb, buffer, sizeof(sb));
    cout << sb.s_blocks_count << endl;
    cout << sb.s_free_blocks_count << endl;
    cout << sb.s_r_blocks_count << endl;
}
