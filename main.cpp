#include "ext2_fs.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdint>
using namespace std;

const int BOOT_BLOCK_SIZE = 1024;

#define PRINT(x) cout << #x << " = " << x << endl;

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

	PRINT(sb.s_inodes_count)
	PRINT(sb.s_blocks_count)
	PRINT(sb.s_r_blocks_count)
	PRINT(sb.s_free_blocks_count)
	PRINT(sb.s_free_inodes_count)
	PRINT(sb.s_first_data_block)
	PRINT(sb.s_log_block_size)
	PRINT(sb.s_log_frag_size)
	PRINT(sb.s_blocks_per_group)
	PRINT(sb.s_frags_per_group)
	PRINT(sb.s_inodes_per_group)
	PRINT(sb.s_mtime)
	PRINT(sb.s_wtime)
	PRINT(sb.s_mnt_count)
	PRINT(sb.s_max_mnt_count)
	PRINT(sb.s_magic)
	PRINT(sb.s_state)
	PRINT(sb.s_errors)
	PRINT(sb.s_minor_rev_level)
	PRINT(sb.s_lastcheck)
	PRINT(sb.s_checkinterval)
	PRINT(sb.s_creator_os)
	PRINT(sb.s_rev_level)
	PRINT(sb.s_def_resuid)
	PRINT(sb.s_def_resgid)

    uint32_t block_size = 1024 << sb.s_log_block_size;   
    //block_group_descriptor
    ext2_group_desc group_desc;
    uint32_t block_group_descriptor = sb.s_first_data_block+1;     

    int group = 0;
    while(group * sb.s_inodes_per_group < sb.s_inodes_count)
    {
        cout << endl;
        cout << "****************************************" << endl;
        cout << "********** GROUP " << group << " *******************" << endl;
        cout << "****************************************" << endl;
        read_data_from_address(&group_desc, sizeof(group_desc),
                                block_size * block_group_descriptor + 32 * group);
        PRINT(group_desc.bg_block_bitmap)
        PRINT(group_desc.bg_inode_bitmap)
        PRINT(group_desc.bg_inode_table)
        PRINT(group_desc.bg_free_blocks_count)
        PRINT(group_desc.bg_free_inodes_count)
        PRINT(group_desc.bg_used_dirs_count)
        PRINT(group_desc.bg_pad)

        int i = 0;
        int inode_bitmap_block = group_desc.bg_inode_bitmap;
        cout << "Inodes:";
        while(i < sb.s_inodes_per_group)
        {
            read_block(1024, inode_bitmap_block, buffer);
            for(int byte = 0; byte < 1024; ++byte)
            {
                for(int bit = 0; bit < 8; ++bit)
                {
                    if((buffer[byte] & (1<<bit)) != 0) cout << " " << i ;
                    ++i;
                    if(i == sb.s_inodes_per_group) break;
                }
                if(i == sb.s_inodes_per_group) break;
            }
            ++inode_bitmap_block;
        }
        cout << endl;
        /*
        i = 0;
        int block_bitmap_block = group_desc.bg_block_bitmap;
        cout << "Blocks:";
        while(i < sb.s_blocks_per_group)
        {
            cout << "Reading block:" << block_bitmap_block << endl;
            read_block(1024, block_bitmap_block, buffer);
            for(int byte = 0; byte < 1024; ++byte)
            {
                for(int bit = 0; bit < 8; ++bit)
                {
                    //if(buffer[byte] & (1<<bit) != 0) cout << " " << i ;
                    ++i;
                    if(i == sb.s_blocks_per_group) break;
                }
                if(i == sb.s_blocks_per_group) break;
            }
            ++block_bitmap_block;
        }
        cout << endl;
        */
        group++;
    }
}
