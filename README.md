# AzorTable
C-99 Table library

# Guide
* Create table

```c
  Table table = Table_new();
```

* Add column to table

```c
Table_add_column(table, 11, "Real Column", table_COLUMN_LEFT, table_COLUMN_REAL);
Table_add_column(table, 14, "Integer Column", table_COLUMN_LEFT, table_COLUMN_INTEGER);
Table_add_column(table, 11, "Bool Column", table_COLUMN_LEFT, table_COLUMN_BOOL);
Table_add_column(table, 13, "String Column", table_COLUMN_LEFT, table_COLUMN_STRING);
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
 Table_add_row(table, 1.5f, 1, 1, "first string");
 Table_add_row(table, 2.5f, 6, 0, "second string");
 Table_add_row(table, 3.9f, 10, 1, "third string");
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
 
 | Column 1 | Column 2 | Column 3 | Column 4      |
 | -------- | -------- | -------- | ------------- |
 | 1.5      | 1        | true     | first string  |
 | 2.5      | 6        | false    | second string |
 | 3.9      | 10       | true     | third string  |
