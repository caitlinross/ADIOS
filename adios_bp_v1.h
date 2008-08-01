struct adios_bp_buffer_struct_v1
{
    int f;             // the file handle
    uint64_t file_size;
    uint32_t version;

    char * allocated_buff_ptr;  // initial alloc for aligning on 8-byte boundary

    char * buff;
    uint64_t length;
    uint64_t offset;   // buffer_offset

    enum ADIOS_FLAG change_endianness;

    off_t file_offset;
    uint64_t end_of_pgs;          // where the last process group ends
    uint64_t pg_index_offset;     // process groups index starts
    uint64_t pg_size;             // process groups index size
    uint64_t vars_index_offset;   // vars index start
    uint64_t vars_size;           // vars index size

    uint64_t read_pg_offset;
    uint64_t read_pg_size;
};

struct adios_index_process_group_struct_v1
{
    char * group_name;
    uint32_t process_id;
    uint32_t timestep;
    uint64_t offset_in_file;

    struct adios_index_process_group_struct_v1 * next;
};

struct adios_index_var_entry_struct_v1
{
    uint64_t offset;
    void * min;
    void * max;
};

struct adios_index_var_struct_v1
{
    char * group_name;
    char * var_name;
    char * var_path;
    enum ADIOS_DATATYPES type;

    uint64_t entries_count;
    uint64_t entries_allocated;

    struct adios_index_var_entry_struct_v1 * entries;

    struct adios_index_var_struct_v1 * next;
};

struct adios_method_info_struct_v1
{
    enum ADIOS_IO_METHOD id;
    char * parameters;

    struct adios_method_info_struct_v1 * next;
};

struct adios_dimension_item_struct_v1
{
    uint64_t rank;
    uint16_t var_id;
};

struct adios_dimension_struct_v1
{
    struct adios_dimension_item_struct_v1 dimension;
    struct adios_dimension_item_struct_v1 global_dimension;
    struct adios_dimension_item_struct_v1 local_offset;
    struct adios_dimension_struct_v1 * next;
};

struct adios_process_group_header_struct_v1
{
    enum ADIOS_FLAG host_language_fortran;
    char * name;
    uint16_t coord_comm_id;
    uint16_t coord_var_id;
    uint16_t timestep_id;
    uint8_t methods_count;
    struct adios_method_info_struct_v1 * methods;
};

struct adios_vars_header_struct_v1
{
    uint32_t count;
    uint64_t length;
};

struct adios_attributes_header_struct_v1
{
    uint16_t count;
    uint64_t length;
};

struct adios_var_header_struct_v1
{
    uint16_t id;
    char * name;
    char * path;
    enum ADIOS_DATATYPES type;
    enum ADIOS_FLAG is_dim;
    struct adios_dimension_struct_v1 * dims;
    uint64_t payload_size;
};

struct adios_var_payload_struct_v1
{
    void * min;
    void * max;
    void * payload;
};

struct adios_attribute_struct_v1
{
    uint16_t id;
    char * name;
    char * path;

    enum ADIOS_FLAG is_var;

    uint16_t var_id;

    enum ADIOS_DATATYPES type;
    uint32_t length;
    void * value;
};

void adios_buffer_struct_init (struct adios_bp_buffer_struct_v1 * b);
void adios_buffer_struct_clear (struct adios_bp_buffer_struct_v1 * b);

void * adios_dupe_data_scalar (enum ADIOS_DATATYPES type, void * in);

// buff must be 4 bytes
int adios_parse_version (struct adios_bp_buffer_struct_v1 * b
                        ,uint32_t * version
                        );

// buff must be 16 bytes
int adios_parse_index_offsets_v1 (struct adios_bp_buffer_struct_v1 * b);

int adios_parse_process_group_index_v1 (struct adios_bp_buffer_struct_v1 * b
                         ,struct adios_index_process_group_struct_v1 ** pg_root
                         );

int adios_parse_vars_index_v1 (struct adios_bp_buffer_struct_v1 * b
                              ,struct adios_index_var_struct_v1 ** vars_root
                              );

int adios_parse_process_group_header_v1 (struct adios_bp_buffer_struct_v1 * b
                     ,struct adios_process_group_header_struct_v1 * pg_header
                     );

int adios_parse_vars_header_v1 (struct adios_bp_buffer_struct_v1 * b
                               ,struct adios_vars_header_struct_v1 * vars_header
                               );

int adios_parse_var_data_header_v1 (struct adios_bp_buffer_struct_v1 * b
                                ,struct adios_var_header_struct_v1 * var_header
                                );

int adios_parse_var_data_payload_v1 (struct adios_bp_buffer_struct_v1 * b
                              ,struct adios_var_header_struct_v1 * var_header
                              ,struct adios_var_payload_struct_v1 * var_payload
                              );

int adios_parse_attributes_header_v1 (struct adios_bp_buffer_struct_v1 * b
                       ,struct adios_attributes_header_struct_v1 * attrs_header
                       );

int adios_parse_attribute_v1 (struct adios_bp_buffer_struct_v1 * b
                             ,struct adios_attribute_struct_v1 * attribute
                             );

// ****************************************************************************
// functions from adios_posix.c used for file reading

void adios_init_buffer_read_version (struct adios_bp_buffer_struct_v1 * b);
void adios_posix_read_version (struct adios_bp_buffer_struct_v1 * b);

void adios_init_buffer_read_index_offsets (
                                         struct adios_bp_buffer_struct_v1 * b
                                         );
void adios_posix_read_index_offsets (struct adios_bp_buffer_struct_v1 * b);

void adios_init_buffer_read_process_group_index (
                                          struct adios_bp_buffer_struct_v1 * b
                                          );
void adios_posix_read_process_group_index (struct adios_bp_buffer_struct_v1 * b
                                          );

void adios_init_buffer_read_vars_index (struct adios_bp_buffer_struct_v1 * b);
void adios_posix_read_vars_index (struct adios_bp_buffer_struct_v1 * b);

void adios_init_buffer_read_procss_group (struct adios_bp_buffer_struct_v1 * b);
uint64_t adios_posix_read_process_group (struct adios_bp_buffer_struct_v1 * b);

int adios_posix_open_read_internal (const char * filename
                                   ,const char * base_path
                                   ,struct adios_bp_buffer_struct_v1 * b
                                   );
void adios_posix_close_internal (struct adios_bp_buffer_struct_v1 * b);
