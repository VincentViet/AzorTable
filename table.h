//
// Created by vice on 11/05/2019.
//

#ifndef __azor_table__
#define __azor_table__

#include <string.h>

#ifndef _TABLE_MAX_COLUMN
#define _TABLE_MAX_COLUMN       100
#endif

#ifndef _TABLE_MAX_ROW
#define _TABLE_MAX_ROW          100
#endif

#ifndef _TABLE_MAX_LINE_LENGTH
#define _TABLE_MAX_LINE_LENGTH  1000
#endif

#ifndef _TABLE_MAX_LINE_LENGTH
#define _TABLE_MAX_LINE_LENGTH  1000
#endif


typedef struct table_t          *Table;

typedef enum col_style_e{
    table_COLUMN_LEFT,
    table_COLUMN_RIGHT
} ColumnStyle;

typedef enum col_data_type_e{
    table_COLUMN_REAL,
    table_COLUMN_INTEGER,
    table_COLUMN_BOOL,
    table_COLUMN_STRING
} ColumnDataType;

Table   Table_new(void);
void    Table_free(Table table);
void    Table_add_column(Table table, size_t width, const char* name, ColumnStyle style, ColumnDataType dt_type);
void    Table_add_row(Table table, ...);
void    Table_print(Table table);

#endif //__azor_table__
