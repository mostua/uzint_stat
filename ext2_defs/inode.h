struct inode
{
	short i_mode;
	short i_uid;
	int i_size;
	int i_atime;
	int i_ctime;
	int i_mtime;
	int i_dtime;
	short i_gid;
	short i_links_count;
	int i_blocks;
	int i_flags;
	int i_osd1;
	int i_block[15];
	int i_generation;
	int i_file_acl;
	int i_dir_acl;
	int i_faddr;
	char i_osd2[12]; //to consider
};
