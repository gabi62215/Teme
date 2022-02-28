#ifndef __STRUCTURES__
#define __STRUCTURES__

#define MAX_COLUMN_NAME_LEN 30
#define MAX_TABLE_NAME_LEN  30
#define MAX_DB_NAME_LEN     30
#define MAX_CMD_LEN         300

// int
typedef struct intCell {
	int    value;
	struct intCell* next;
} t_intCell;

typedef struct intLine {
	t_intCell*      cells;
	struct intLine* next;
} t_intLine;

// float
typedef struct floatCell {
	float  value;
	struct floatCell* next;
} t_floatCell;

typedef struct floatLine {
	t_floatCell*      cells;
	struct floatLine* next;
} t_floatLine;

// string
typedef struct stringCell {
	char*  value;
	struct stringCell* next;
} t_stringCell;

typedef struct stringLine {
	t_stringCell*       cells;
	struct stringLine* next;
} t_stringLine;

// cell type
typedef enum {
	INT,
	FLOAT,
	STRING
} t_cellType;

// column
typedef struct column {
	char name[MAX_COLUMN_NAME_LEN];
	struct column* next;
} t_column;

// table
typedef struct table {
	char name[MAX_TABLE_NAME_LEN];
	t_cellType    type;
	t_column*     columns;
	void*         lines;  // t_intLine* | t_floatLine* | t_stringLine*
	struct table* next;
} t_table;

// database
typedef struct db {
	char name[MAX_DB_NAME_LEN];
	t_table* tables;
} t_db;

//FUNCTII
t_db *INIT_DB(char *name);
int CREATE(t_db *database,char *arguments);
void PRINT_DB(t_db *database);
void printTable(t_table *table);
void printLines(t_table *table);
void printColumns(t_table *table);
int addTable(t_table **table,char *name,t_cellType type);
t_table *alocTable(char *name,t_cellType type);
t_column *alocColumn(char *name);
int addColumn(t_column **column,char *name);
void DELETE_DB(t_db **database);
void deleteColumn(t_column **column);
void deleteIntLine(void **int_line);
void deleteFloatLine(void **float_line);
void deleteStringLine(void **string_line);
void deleteTable(t_table **table);
int deleteTheTable(t_db *database,char *table_name);
int printTheTable(t_db *database,char *table_name);
int addLine(t_db *database,char *values);
t_stringCell *alocStringCell(char *name);
int addStringCell(t_stringCell **string_cell,char *name);
t_floatCell *alocFloatCell(float value);
int addFloatCell(t_floatCell **float_cell,float value);
t_intCell *alocIntCell(int value);
int addIntCell(t_intCell **int_cell,int value);
t_stringLine *alocStringLine();
int addStringLine(void **string_line);
t_floatLine *alocFloatLine();
int addFloatLine(void **float_line);
t_intLine *alocIntLine();
int addIntLine(void **int_line);
void CLEAR(t_db *database,char *table_name);
void printIntLine(t_intCell *int_cell);
void printFLoatLine(t_floatCell *float_cell);
void printStringLine(t_stringCell *string_cell);
void intEqual(t_table *table,int value,int i_column);
void intGreater(t_table *table,int value,int i_column);
void intLess(t_table *table,int value,int i_column);
void intGreaterEqual(t_table *table,int value,int i_column);
void intLessEqual(t_table *table,int value,int i_column);
void intNotEqual(t_table *table,int value,int i_column);
void floatEqual(t_table *table,float value,int i_column);
void floatGreater(t_table *table,float value,int i_column);
void floatLess(t_table *table,float value,int i_column);
void floatGreaterEqual(t_table *table,float value,int i_column);
void floatLessEqual(t_table *table,float value,int i_column);
void floatNotEqual(t_table *table,float value,int i_column);
void stringEqual(t_table *table,char *value,int i_column);
void stringGreater(t_table *table,char *value,int i_column);
void stringLess(t_table *table,char *value,int i_column);
void stringGreaterEqual(t_table *table,char *value,int i_column);
void stringLessEqual(t_table *table,char *value,int i_column);
void stringNotEqual(t_table *table,char *value,int i_column);
void SEARCH(t_db *database,char *arguments);
void deleteIntCell(t_intCell **int_cell);
void deleteFloatCell(t_floatCell **float_cell);
void deleteStringCell(t_stringCell **string_cell);
void intEqualDelete(t_table *table,int value,int i_column);
void intGreaterDelete(t_table *table,int value,int i_column);
void intLessDelete(t_table *table,int value,int i_column);
void intGreaterEqualDelete(t_table *table,int value,int i_column);
void intLessEqualDelete(t_table *table,int value,int i_column);
void intNotEqualDelete(t_table *table,int value,int i_column);
void floatEqualDelete(t_table *table,float value,int i_column);
void floatGreaterDelete(t_table *table,float value,int i_column);
void floatLessDelete(t_table *table,float value,int i_column);
void floatGreaterEqualDelete(t_table *table,float value,int i_column);
void floatLessEqualDelete(t_table *table,float value,int i_column);
void floatNotEqualDelete(t_table *table,float value,int i_column);
void stringEqualDelete(t_table *table,char *value,int i_column);
void stringGreaterDelete(t_table *table,char *value,int i_column);
void stringLessDelete(t_table *table,char *value,int i_column);
void stringGreaterEqualDelete(t_table *table,char *value,int i_column);
void stringLessEqualDelete(t_table *table,char *value,int i_column);
void stringNotEqualDelete(t_table *table,char *value,int i_column);
void DELETE(t_db *database,char *arguments);
#endif