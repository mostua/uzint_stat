struct super_block
{
	int s_inodes_count;
	int s_blocks_count;
	int s_r_blocks_count;
	int s_free_blocks_count;
	int s_free_inodes_count;
	int s_first_data_block;
	int s_log_block_size;
	int s_log_frag_size;
	int s_blocks_per_group;
	int s_frags_per_group;
	int s_inodes_per_group;
	int s_mtime;
	int s_wtime;
	short s_mnt_count;
	short s_max_mnt_count;
	short s_magic;
	short s_state;
	short s_errors;
	short s_minor_rev_level;
	int s_lastcheck;
	int s_checkinerval;
	int s_creator_os;
	int s_rev_level;
	short s_def_resuid;
	short s_def_resgid;
};
