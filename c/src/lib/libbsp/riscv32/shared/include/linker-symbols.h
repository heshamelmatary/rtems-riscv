#ifndef LIBBSP_RISCV_SHARED_LINKER_SYMBOLS_H
#define LIBBSP_RISCV_SHARED_LINKER_SYMBOLS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup riscv_linker Linker Support
 *
 * @ingroup riscv_shared
 *
 * @brief Linker support.
 *
 * @{
 */

#ifndef ASM
  #define LINKER_SYMBOL(sym) extern char sym [];
#else
  #define LINKER_SYMBOL(sym) .extern sym
#endif

LINKER_SYMBOL(bsp_section_start_begin)
LINKER_SYMBOL(bsp_section_start_end)
LINKER_SYMBOL(bsp_section_start_size)

LINKER_SYMBOL(bsp_section_vector_begin)
LINKER_SYMBOL(bsp_section_vector_end)
LINKER_SYMBOL(bsp_section_vector_size)

LINKER_SYMBOL(bsp_section_text_begin)
LINKER_SYMBOL(bsp_section_text_end)
LINKER_SYMBOL(bsp_section_text_size)
LINKER_SYMBOL(bsp_section_text_load_begin)
LINKER_SYMBOL(bsp_section_text_load_end)

LINKER_SYMBOL(bsp_section_rodata_begin)
LINKER_SYMBOL(bsp_section_rodata_end)
LINKER_SYMBOL(bsp_section_rodata_size)
LINKER_SYMBOL(bsp_section_rodata_load_begin)
LINKER_SYMBOL(bsp_section_rodata_load_end)

LINKER_SYMBOL(bsp_section_data_begin)
LINKER_SYMBOL(bsp_section_data_end)
LINKER_SYMBOL(bsp_section_data_size)
LINKER_SYMBOL(bsp_section_data_load_begin)
LINKER_SYMBOL(bsp_section_data_load_end)

LINKER_SYMBOL(bsp_section_bss_begin)
LINKER_SYMBOL(bsp_section_bss_end)
LINKER_SYMBOL(bsp_section_bss_size)

LINKER_SYMBOL(bsp_section_work_begin)
LINKER_SYMBOL(bsp_section_work_end)
LINKER_SYMBOL(bsp_section_work_size)

LINKER_SYMBOL(bsp_section_stack_begin)
LINKER_SYMBOL(bsp_section_stack_end)
LINKER_SYMBOL(bsp_section_stack_size)

LINKER_SYMBOL(bsp_vector_table_begin)
LINKER_SYMBOL(bsp_vector_table_end)
LINKER_SYMBOL(bsp_vector_table_size)

LINKER_SYMBOL(bsp_start_vector_table_begin)
LINKER_SYMBOL(bsp_start_vector_table_end)
LINKER_SYMBOL(bsp_start_vector_table_size)

LINKER_SYMBOL(bsp_translation_table_base)
LINKER_SYMBOL(bsp_translation_table_end)

LINKER_SYMBOL(_bsp_processor_count)

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_RISCV_SHARED_LINKER_SYMBOLS_H */
