//
// Created by vice on 11/05/2019.
//

#include "table.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>

#define printf_error(fmt, ...)          do{printf("\033[1;31m");printf(fmt"\n", __VA_ARGS__);printf("\033[0m");}while(0)

#define _TABLE_COLUMN_FMT_SIZE          8

typedef union table_data_t{
    float _real;
    int   _integer;
    const char* _string;
} TableData;

typedef struct table_column_t{
    int _width;
    const char* _name;
    char _fmt[_TABLE_COLUMN_FMT_SIZE];
    ColumnStyle _style;
    ColumnDataType _dt_type;
} TableColumn;



struct table_t{
    TableColumn _columns[_TABLE_MAX_COLUMN];
    TableData   _rows[_TABLE_MAX_COLUMN * _TABLE_MAX_ROW];

    int _rows_size;
    int _line_width;
    int _columns_size;
};
Table Table_new(void) {
    Table new_table = malloc(sizeof(struct table_t));
    if (!new_table){
        printf_error("%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
        return NULL;
    }

    new_table->_columns_size = 0;
    new_table->_rows_size = 0;
    new_table->_line_width = 0;
    return new_table;
}

void Table_free(Table table) {
    free(table);
}

void Table_add_column(Table table, size_t width, const char *name, ColumnStyle style, ColumnDataType dt_type) {
    if (table->_columns_size < _TABLE_MAX_COLUMN)
    {
        TableColumn* column = table->_columns + table->_columns_size++;
        column->_width = width + 2;
        column->_name = name;
        column->_style = style;
        column->_dt_type = dt_type;
        if (dt_type == table_COLUMN_REAL)
        {
            if (style == table_COLUMN_LEFT)
                strcpy(column->_fmt, "|%-*g|");
            else if (style == table_COLUMN_RIGHT)
                strcpy(column->_fmt, "|%*g|");
        }
        else if (dt_type == table_COLUMN_INTEGER)
        {
            if (style == table_COLUMN_LEFT)
                strcpy(column->_fmt, "|%-*d|");
            else if (style == table_COLUMN_RIGHT)
                strcpy(column->_fmt, "|%*d|");
        }
        else if (dt_type == table_COLUMN_BOOL || dt_type == table_COLUMN_STRING)
        {
            if (style == table_COLUMN_LEFT)
                strcpy(column->_fmt, "|%-*s|");
            else if (style == table_COLUMN_RIGHT)
                strcpy(column->_fmt, "|%*s|");
        }

        table->_line_width += column->_width;
    } else{
        printf_error("%s:%d: %s\n", __FILE__, __LINE__, "Table columns is full");
    }
}

void Table_add_row(Table table, ...) {
    if (table->_rows_size < _TABLE_MAX_ROW)
    {
        va_list  argv;
        va_start(argv, table);
        TableData* row = table->_rows + table->_rows_size++ * table->_columns_size;
        for (int i = 0; i < table->_columns_size; ++i) {
            switch (table->_columns[i]._dt_type)
            {
                case table_COLUMN_REAL:
                    (row + i)->_real = (float)va_arg(argv, double);
                    break;
                case table_COLUMN_INTEGER:
                    (row + i)->_integer = va_arg(argv, int);
                    break;
                case table_COLUMN_BOOL:
                    (row + i)->_string = va_arg(argv, int) ? "true" : "false";
                    break;
                case table_COLUMN_STRING:
                    (row + i)->_string = va_arg(argv, const char*);
                    break;
            }
        }
        va_end(argv);
    } else
        printf_error("%s:%d: %s\n", __FILE__, __LINE__, "Table rows is full");
}

void Table_print(Table table) {
    /*print columns*/
    char line[table->_line_width];
    memset(line, 0, table->_line_width);

    char* content;
    TableColumn* col;
    for (int i = 0; i < table->_columns_size; ++i) {
        col = table->_columns + i;
        content = malloc(col->_width);

        if (col->_style == table_COLUMN_LEFT)
            sprintf(content, "|%-*s|", col->_width - 2, col->_name);
        else if (col->_style == table_COLUMN_RIGHT)
            sprintf(content, "|%*s|", col->_width - 2, col->_name);

        if (!i)
            strcpy(line, content);
        else
            strncat(line, content, col->_width);

        free(content);
    }
    printf("%s\n", line);
    memset(line, 0, table->_line_width);

    /*print rows*/
    for (int i = 0; i < table->_rows_size; ++i) {
        TableData* row = table->_rows + i * table->_columns_size;
        for (int j = 0; j < table->_columns_size; ++j) {
            col = table->_columns + j;
            content = malloc(col->_width);

            if (col->_dt_type == table_COLUMN_REAL)
                sprintf(content, col->_fmt, col->_width - 2, (row + j)->_real);
            else if (col->_dt_type == table_COLUMN_INTEGER)
                sprintf(content, col->_fmt, col->_width - 2, (row + j)->_integer);
            else if (col->_dt_type ==  table_COLUMN_BOOL || col->_dt_type == table_COLUMN_STRING)
                sprintf(content, col->_fmt, col->_width - 2, (row + j)->_string);

            if (!j)
                strcpy(line, content);
            else
                strncat(line, content, col->_width);

            free(content);
        }
        printf("%s\n", line);
        memset(line, 0, table->_line_width);
    }
}
