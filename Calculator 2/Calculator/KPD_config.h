

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_



#define KPD_PORT_Col                Port_D
#define KPD_PORT_Row                Port_C
#define KPD_NO_PRESSED_KEY       	0xFF
/*****************define pins***********************/
#define KPD_COLUMN_0            	 Pin1
#define KPD_COLUMN_1           	     Pin2
#define KPD_COLUMN_2             	 Pin3
#define KPD_COLUMN_3            	 Pin4

#define KPD_ROW_0              	     Pin1
#define KPD_ROW_1              	     Pin2
#define KPD_ROW_2                    Pin3
#define KPD_ROW_3                    Pin4

/*****row and column numbers for array*************/
#define ROW_NUM                  4
#define COLUMN_NUM               4
/****************the value of array (keypad)**************/
#define KPD_ARR_VAL      {{'7','8','9','/'},\
	                     {'4','5','6','*'},\
					     {'1','2','3','-'},\
						 {'C','0','=','+'}}



#endif /* KPD_CONFIG_H_ */
