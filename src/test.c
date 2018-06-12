#include "test.h"
#include "memory.h"

int32_t Verify_mem(char *code_ic){
		int i;
		const char *mem_pointer = memory;
		for(i=0;i<strlen(memory);i++){
			if(*(mem_pointer+i)=='N'){
				int j;
				char code_ic_temp[6];
				for(j=0;*(mem_pointer+i+j+1)!='_';j++){
					code_ic_temp[j]=*(mem_pointer+i+j+1);
				}
				if(strcmp(code_ic_temp,code_ic)==0){
					return i;
				}
			}
		}
		return -1;
}

uint32_t GPIO_config(int pos){
		int i = pos;
		const char *mem_pointer = memory;
		do{
		i++;
		}while(*(mem_pointer+i)!='P');
		int j;
		for(j=1;*(mem_pointer+j+i)!='_';j++){
			if(*(mem_pointer+j+i)=='0'){
				Set_Input(j);
			}
			else{
				Set_Output(j);
			}
		}
		return Exec_teste(i+j+1);
}

uint32_t Char_toHex(int pos){
	int j = 0, pino = 0, resultado = 0;
	const char *mem_pointer = memory;
	for(j=0;j<13;j++){
		pino = *(mem_pointer+pos+j) == '1'? 1:0;
		resultado |= (pino<<(12-j));
	}
	return resultado; 
}

uint32_t Exec_teste(int pos){
		int i,teste,port_input,port_test;
		const char *mem_pointer = memory;
		for(i=pos+1;*(mem_pointer+i-1)!='N';i=i+15){
			teste = Char_toHex(i);
			PortK_Output(0x7F & teste);
			PortN_Output(teste>>7);
			port_input = PortK_Input() & (PortN_Input()<<6);
			port_test = teste & ~(GPIO_PORTK_DIR_R&(GPIO_PORTN_DIR_R<<6));
			if(port_input!=port_test){
				return (port_input^port_test);
			}	
		}
		return 1;
}
