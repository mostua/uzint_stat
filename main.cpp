#include "ext2_fs.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdint>
using namespace std;

const int BOOT_BLOCK_SIZE = 1024;

char buffer[1024];
ifstream* partition;

void read_data_from_address(void * dst, size_t size, uint32_t address) {
    partition->seekg(address, partition->beg);
    partition->read((char*)dst, size);
}

void read_block(int block_size, uint32_t id, void * dst) {
    read_data_from_address(dst, block_size, block_size * id);
}

int main(int argc, char ** argv)
{
    if(argc < 2)
        return 1;
    ext2_super_block sb;
    ext2_inode in;
    ifstream part(argv[1], ifstream::binary);
    partition = &part;
    read_data_from_address(&sb, sizeof(sb), BOOT_BLOCK_SIZE);
    cout << sb.s_blocks_count << endl;
    cout << sb.s_free_blocks_count << endl;
    cout << sb.s_r_blocks_count << endl;
    uint32_t block_size = 1024 << sb.s_log_block_size;   
    //block_group_descriptor
    ext2_group_desc group_desc;
    uint32_t block_group_descriptor = sb.s_first_data_block+1;     
    read_data_from_address(&group_desc, sizeof(group_desc),
                            block_size * block_group_descriptor);
    cout << group_desc.bg_inode_table;
    

}
