#include "ext2_fs.h"
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>
using namespace std;

const int BOOT_BLOCK_SIZE = 1024;

template<typename T>
void printInfo(std::string information, T value) {
    cout << information << "\t" << value << endl;
}

char buffer[8096]; //when block size is greater than 8096, change it
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
    
    printInfo("Inode count: ", sb.s_inodes_count);

	printInfo("Block count: ",sb.s_blocks_count);
	printInfo("Reserved block count: ",sb.s_r_blocks_count);
	printInfo("Free blocks:",sb.s_free_blocks_count);
	printInfo("Free inodes:",sb.s_free_inodes_count);
	printInfo("First block:",sb.s_first_data_block);
	printInfo("Block size:",sb.s_log_block_size);
	printInfo("Block size: ", 1024 << sb.s_log_frag_size);
	printInfo("Blocks per group:",sb.s_blocks_per_group);
	printInfo("Fragments per group: ", sb.s_frags_per_group);
	printInfo("Inodes per group: ", sb.s_inodes_per_group);
	printInfo("Last mount time;", sb.s_mtime);
	printInfo("Last write time:", sb.s_wtime);
	printInfo("Mount count: ", sb.s_mnt_count);
	printInfo("Maximum mount count:", sb.s_max_mnt_count);
	printInfo("Filesystem magic number: ", sb.s_magic);
	printInfo("File system state:", sb.s_state);
	printInfo("Behaviour when detecting errors: ", sb.s_errors);
	printInfo("Minor revision level ", sb.s_minor_rev_level);
	printInfo("Last checked: ", sb.s_lastcheck);
	printInfo("Check interval: ", sb.s_checkinterval);
	printInfo("OS:", sb.s_creator_os);
	printInfo("Revision level:", sb.s_rev_level);
	printInfo("Default uid for reserved blocks:", sb.s_def_resuid);
	printInfo("Default gid for reserved blocks:", sb.s_def_resgid);
	printInfo("First inode:", sb.s_first_inode);
	printInfo("Inode size:", sb.s_inode_size);

    uint32_t block_size = 1024 << sb.s_log_block_size;   
    //block_group_descriptor
    ext2_group_desc group_desc;
    uint32_t block_group_descriptor = sb.s_first_data_block+1;     

    int group = 0;
    while(group * sb.s_inodes_per_group < sb.s_inodes_count)
    {
        cout << endl;
        cout << "****************************************" << endl;
        cout << "************ GROUP " << group << " *******************" << endl;
        cout << "****************************************" << endl;
        read_data_from_address(&group_desc, sizeof(group_desc),
                                block_size * block_group_descriptor + 32 * group);
        printInfo("Block bitmap", group_desc.bg_block_bitmap);
        printInfo("Inode bitmap:", group_desc.bg_inode_bitmap);
        printInfo("Inode table:", group_desc.bg_inode_table);
        printInfo("Free blocks:", group_desc.bg_free_blocks_count);
        printInfo("Free inodes:", group_desc.bg_free_inodes_count);
        printInfo("Directory count:", group_desc.bg_used_dirs_count);
        //printInfo("group_desc.bg_pad)

        int i = 0;
        int inode_bitmap_block = group_desc.bg_inode_bitmap;
        cout << "Inodes:";
        while(i < sb.s_inodes_per_group)
        {
            read_block(block_size, inode_bitmap_block, buffer);
            for(int byte = 0; byte < block_size; ++byte)
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
        group++;
    }
}
