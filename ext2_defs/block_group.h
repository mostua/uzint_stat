#ifndef BLOCK_GROUP_H
#define BLOCK_GROUP_H

#include "typedefs.h"

struct block_group
{
	int bg_block_bitmap;
	int bg_inode_bitmap;
	int bg_inode_table;
	short bg_free_blocks_count;
	short bg_free_inodes_count;
	short bg_used_dirs_count;
	short bg_pad;
	char bg_reserved[12];
};

#endif
