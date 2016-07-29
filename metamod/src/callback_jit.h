#pragma once

#define CDATA_ENTRY(s, x, p, h)	{#x, offsetof(s, x), getArgsCount(decltype(s##::##x)()), !is_void(decltype(s##::##x)()), is_varargs(decltype(s##::##x)()), p, h}

struct jitdata_t
{
	size_t pfn_original;
	uint8 args_count;
	bool has_ret;
	bool has_varargs;
	uint8 mm_hook_time;
	size_t pfn_offset; // from fn table
	size_t mm_hook;

	MPlugin* plugins;
	int plugins_count;
	size_t table_offset; // from MPlugin
	size_t post_table_offset; // from MPlugin
};

struct compile_data_t
{
	const char* name;
	size_t offset;
	uint8 args_count;
	bool has_ret;
	bool has_varargs;
	uint8 mm_hook_time;
	size_t mm_hook;
};

template<typename ret_t, typename ...t_args>
size_t getArgsCount(ret_t (*)(t_args...))
{
	return sizeof...(t_args);
}

template<typename ret_t, typename ...t_args>
size_t getArgsCount(ret_t (*)(t_args..., ...))
{
	return sizeof...(t_args);
}

template<typename ...t_args>
bool is_void(void (*)(t_args...))
{
	return true;
}

template<typename ...t_args>
bool is_void(void (*)(t_args..., ...))
{
	return true;
}

template<typename ret_t, typename ...t_args>
bool is_void(ret_t (*)(t_args..., ...))
{
	return false;
}

template<typename ret_t, typename ...t_args>
bool is_void(ret_t (*)(t_args...))
{
	return false;
}

template<typename ret_t, typename ...t_args>
bool is_varargs(ret_t (*)(t_args...))
{
	return false;
}

template<typename ret_t, typename ...t_args>
bool is_varargs(ret_t (*)(t_args..., ...))
{
	return true;
}

class CJit
{
public:
	size_t compile_callback(jitdata_t* jitdata);
	size_t compile_tramp(size_t ptr_to_func/*, size_t hook, size_t hook_time*/);
	void clear_callbacks();

private:
	static bool is_hook_needed(jitdata_t* jitdata);

private:
	execmem_allocator m_allocator;
	execmem_allocator m_static_allocator;
};

extern CJit g_jit;
