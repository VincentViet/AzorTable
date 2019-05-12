# AzorTable
C-99 Table library

# Guide
* Create table

```c
  Table table = Table_new();
```

* Add column to table

```c
Table_add_column(table, 7, "Column 1", table_COLUMN_LEFT, table_COLUMN_INTEGER);
Table_add_column(table, 7, "Column 2", table_COLUMN_LEFT, table_COLUMN_INTEGER);
Table_add_column(table, 7, "Column 3", table_COLUMN_LEFT, table_COLUMN_INTEGER);
Table_add_column(table, 7, "Column 4", table_COLUMN_LEFT, table_COLUMN_INTEGER);
```
  
* **enum** `ColumnStyle`: is used to align content when print to console.
  
  No. | ColumnStyle member | Description                                                                  |
  --- | ------------------ | -----------                                                                  |
  1   | table_COLUMN_LEFT  | All contents of this column type will be left aligned when print to console. |
  2   | table_COLUMN_RIGHT | All contents of this column type will be right aligned when print to console.|
  
* **enum** `ColumnDataType`: is used to represent for **C-99** build-in type.
  
  No. | ColumnDataType member | Represented Type|
  --- | --------------------- | --------------- |
  1   | table_COLUMN_REAL     | float           |
  2   | table_COLUMN_INTEGER  | integer         |
  3   | table_COLUMN_BOOL     | boolean         |
  4   | table_COLUMN_STRING   | string          |
 
 * Add row to table
 
 ```c
 Table_add_row(table, 1, 2, 3, 4);
 Table_add_row(table, 5, 6, 7, 8);
 Table_add_row(table, 9, 10, 11, 12);
 ```
 * Print table to console
 ```c
 Table_print(table);
 ```
 
 * Free/delete table memories
 ```c
 Table_free(table);
 ```
 
 * **RESULT**
 
 | Column 1 | Column 2 | Column 3 | Column 4|
 | -------- | -------- | -------- | ------- |
 | 1        | 2        | 3        | 4       |
 | 5        | 6        | 7        | 8       |
 | 9        | 10       | 11       | 12      |
